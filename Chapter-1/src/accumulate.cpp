#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <chrono>

using std::cout;
using std::endl;
using std::thread;
using std::ref;
using std::mem_fn;
using std::accumulate;
using std::distance;
using std::advance;
using std::vector;
using std::for_each;
using std::min;

// accumulate block structure for accumulate
template <class Iterator, class T>
struct accumulate_block {
	// override operator ()
	void operator() (Iterator first, Iterator last, T &result) {
		// write accumulate number into result array
		result = accumulate(first, last, result);
	}
};

// parallel accumulate function
template <class Iterator, class T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
	const auto length = distance(first, last);	// calculate length of target array
	
	if (!length)
		return init;	// empty array no need to calculate

	decltype(length) min_tasks_per_thread = 25;
	decltype(length) max_threads = (length + min_tasks_per_thread - 1) / min_tasks_per_thread;	// ensure no extra thread is spawn if task number is smaller than min_tasks_per_thread
	decltype(length) hardware_threads = thread::hardware_concurrency();	// read device thread concurrency info for true concurrency
	decltype(length) num_threads = min((hardware_threads != 0) ? hardware_threads : 2, max_threads);
	decltype(length) block_size = length / num_threads;

	vector<T> results(num_threads);	// result array
	vector<thread> threads(num_threads - 1);	// thread to be spawn

	Iterator block_start = first;
	cout << num_threads << " threads used for accumulation task!" << endl;
	for (unsigned i = 0; i < num_threads - 1; i++) {	// Iterate only num_threads - 1 time and left the last task for main thread
		Iterator block_end = block_start;
		advance(block_end, block_size);
		threads[i] = thread(accumulate_block<Iterator, T>(), block_start, block_end, ref(results[i]));	// spawn a thread and assign the task
		block_start = block_end;
	}

	results[num_threads - 1] = accumulate(block_start, last, results[num_threads - 1]);	// main thread accumulate last block
	// join all the threads
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

	return accumulate(results.begin(), results.end(), init);
}

int main() {
	vector<long> num(524288);
	unsigned long count = 0;
	for (auto &n : num)
		n = ++count;

	unsigned long acc = 0;

	auto start = std::chrono::steady_clock::now();
	cout << "[reference] " << accumulate(num.begin(), num.end(), acc) << endl;
	auto end = std::chrono::steady_clock::now();
	cout << "execution time: " << std::chrono::duration<double, std::milli> (end - start).count() << " ms" << endl;

	start = std::chrono::steady_clock::now();
	cout << "[parallel] " << parallel_accumulate(num.begin(), num.end(), acc) << endl;
	end = std::chrono::steady_clock::now();
	cout << "execution time: " << std::chrono::duration<double, std::milli> (end - start).count() << " ms" << endl;
	return 0;
}