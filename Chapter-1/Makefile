CC 				= g++

# Directories
INCLUDE_DIR			= include
SRC_DIR				= src
LIB_DIR				= lib
OBJ_DIR				= ../Executable/Chapter-1/obj

# Compiler flags
CPPFLAGS			= -Wall -std=c++11 -I$(INCLUDE_DIR)
# Linker flags
LDFLAGS				= 

# Chapter-1
CHAPTER_1 			= ../Executable/Chapter-1/Chapter-1
CHAPTER_1_OBJ		= $(addprefix $(OBJ_DIR)/, main.o)

# Thread launch object
THREAD_LAUNCH_OBJ 	= $(addprefix $(OBJ_DIR)/, threadLaunch.o)

# Thread guard object
THREAD_GUARD_OBJ 	= $(addprefix $(OBJ_DIR)/, threadGuard.o)

# Parallel accumulator
PARALLEL_ACCUMULATE = ../Executable/Chapter-1/accumulator
PARALLEL_ACCUMULATE_OBJ = $(addprefix $(OBJ_DIR)/, accumulate.o)

# Compile
# $@: The filename representing the target.
# $%: The filename element of an archive member specification.
# $<: The filename of the first prerequisite.
# $?: The names of all prerequisites that are newer than the target, separated by spaces.
# $^: The filenames of all the prerequisites, separated by spaces. This list has duplicate filenames removed since for most uses, such as compiling, copying, etc., duplicates are not wanted.
# $+: Similar to $^, this is the names of all the prerequisites separated by spaces, except that $+ includes duplicates. This variable was created for specific situations such as arguments to linkers where duplicate values have meaning.
# $*: The stem of the target filename. A stem is typically a filename without its suffix. Its use outside of pattern rules is discouraged.
all: $(CHAPTER_1) $(PARALLEL_ACCUMULATE)

$(PARALLEL_ACCUMULATE): $(PARALLEL_ACCUMULATE_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(CHAPTER_1): $(CHAPTER_1_OBJ) $(THREAD_LAUNCH_OBJ) $(THREAD_GUARD_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
# Clean up executables
	rm $(CHAPTER_1) $(PARALLEL_ACCUMULATE)
# Clean up object files
	rm $(CHAPTER_1_OBJ)\
	   $(THREAD_LAUNCH_OBJ) \
	   $(PARALLEL_ACCUMULATE_OBJ)
