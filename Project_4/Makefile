## EECS 281 Advanced Makefile

# How to use this Makefile...
###################
###################
##               ##
##  $ make help  ##
##               ##
###################
###################

# IMPORTANT NOTES:
#   1. Set EXECUTABLE to the command name from the project specification.
#   2. To enable automatic creation of unit test rules, your program logic
#      (where main() is) should be in a file named project*.cpp or
#      specified in the PROJECTFILE variable.
#   3. Files you want to include in your final submission cannot match the
#      test*.cpp pattern.

#######################
# TODO (begin) #
#######################
# Change 'youruniqname' to match your UM uniqname (no quote marks).
UNIQNAME    = hollinsy

# Change the right hand side of the identifier to match the project identifier
# given in the project or lab specification.
IDENTIFIER  = 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9

# Change 'executable' to match the command name given in the project spec.
EXECUTABLE  = zoo

# The following line looks for a project's main() in files named project*.cpp,
# executable.cpp (substituted from EXECUTABLE above), or main.cpp
PROJECTFILE = $(or $(wildcard project*.cpp $(EXECUTABLE).cpp), main.cpp)
# If main() is in another file delete line above, edit and uncomment below
#PROJECTFILE = mymainfile.cpp

# This is the path from the CAEN home folder to where projects will be
# uploaded. (eg. /home/mmdarden/eecs281/project1)
# Change this if you prefer a different path.
# REMOTE_PATH := eecs281_$(EXECUTABLE)_sync  # /home/mmdarden/eecs281_proj0_sync
REMOTE_PATH := eecs281_$(EXECUTABLE)_sync
#######################
# TODO (end) #
#######################

# enables c++17 on CAEN or 281 autograder
PATH := /usr/um/gcc-11.3.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-11.3.0/lib64
LD_RUN_PATH := /usr/um/gcc-11.3.0/lib64

# disable built-in rules
.SUFFIXES:

# designate which compiler to use
CXX         = g++

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# list of test drivers (with main()) for development
TESTSOURCES = $(wildcard test*.cpp)

# list of sources used in project
SOURCES     = $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
# list of objects used in project
OBJECTS     = $(SOURCES:%.cpp=%.o)

# Default Flags
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic

# make debug - will compile sources with $(CXXFLAGS) -g3 and -fsanitize
#              flags also defines DEBUG and _GLIBCXX_DEBUG
debug: CXXFLAGS += -g3 -DDEBUG -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug
.PHONY: debug

# make release - will compile sources with $(CXXFLAGS) and the -O3 flag also
#                defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: $(EXECUTABLE)
.PHONY: release

# make valgrind - will compile sources with $(CXXFLAGS) -g3 suitable for
#                 CAEN or WSL (DOES NOT WORK ON MACOS).
valgrind: CXXFLAGS += -g3
valgrind:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_valgrind
.PHONY: valgrind

# make profile - will compile "all" with $(CXXFLAGS) and the -g3 and -O3 flags
profile: CXXFLAGS += -g3 -O3
profile:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_profile
.PHONY: profile

# make gprof - will compile "all" with $(CXXFLAGS) and the -pg (for gprof)
gprof: CXXFLAGS += -pg
gprof:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_profile
.PHONY: gprof

# make static - will perform static analysis in the matter currently used
#               on the autograder
static:
	cppcheck --enable=all --suppress=missingIncludeSystem \
      $(SOURCES) *.h *.hpp
.PHONY: static

# name of the tarballs created for submission
FULL_SUBMITFILE = fullsubmit.tar.gz
PARTIAL_SUBMITFILE = partialsubmit.tar.gz
UNGRADED_SUBMITFILE = ungraded.tar.gz

# These files are excluded when checking for project identifier (no spaces!)
NO_IDENTIFIER = xcode_redirect.hpp,getopt.h,getopt.c,xgetopt.h

# make identifier - will check to ensure that all source code and header files
#                   include the project identifier, skip subdirectories
#                   also removes old submit tarballs, they are outdated
identifier: $(foreach tsrc,$(TESTSOURCES),$(eval NO_IDENTIFIER := $(NO_IDENTIFIER),$(tsrc)))
identifier:
	@if [ $$(grep --include=*.{h,hpp,c,cpp} --exclude={$(NO_IDENTIFIER)} --directories=skip -L $(IDENTIFIER) * | wc -l) -ne 0 ]; then \
		printf "Missing project identifier in file(s): "; \
		echo `grep --include=*.{h,hpp,c,cpp} --exclude={$(NO_IDENTIFIER)} --directories=skip -L $(IDENTIFIER) *`; \
		exit 1; \
	else \
		rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(UNGRADED_SUBMITFILE); \
	fi
.PHONY: identifier

# Build all executables
all: debug release
all: profile valgrind
.PHONY: all

$(EXECUTABLE): $(OBJECTS)
ifneq ($(EXECUTABLE), executable)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
else
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
endif

# names of test executables
TESTS       = $(TESTSOURCES:%.cpp=%)
# Automatically generate any build rules for test*.cpp files
define make_tests
    ifeq ($$(PROJECTFILE),)
	    @echo Edit PROJECTFILE variable to .cpp file with main\(\)
	    @exit 1
    endif
    SRCS = $$(filter-out $$(PROJECTFILE), $$(SOURCES))
    OBJS = $$(SRCS:%.cpp=%.o)
    HDRS = $$(wildcard *.h *.hpp)
    $(1): CXXFLAGS += -g3 -DDEBUG
    $(1): $$(OBJS) $$(HDRS) $(1).cpp
	$$(CXX) $$(CXXFLAGS) $$(OBJS) $(1).cpp -o $(1)
endef
$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))

alltests: $(TESTS)
.PHONY: alltests

# make clean - remove .o files, executables, tarball
clean:
	rm -Rf *.dSYM
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug
	rm -f $(EXECUTABLE)_valgrind $(EXECUTABLE)_profile $(TESTS) perf.data* \
      $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(UNGRADED_SUBMITFILE)
.PHONY: clean

# Files that should not be included in a tarball
EXCLUDE_FILES = getopt.\?

# get a list of all files that might be included in a submit
# different submit types can do additional filtering to remove unwanted files
FULL_SUBMITFILES=$(filter-out $(TESTSOURCES), \
                   $(wildcard Makefile *.h *.hpp *.cpp test*.txt))

# make fullsubmit.tar.gz - cleans, runs dos2unix, creates tarball
# including test files
$(FULL_SUBMITFILE): $(FULL_SUBMITFILES)
	rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(UNGRADED_SUBMITFILE)
	COPYFILE_DISABLE=true tar --exclude=$(EXCLUDE_FILES) -vczf $(FULL_SUBMITFILE) $(FULL_SUBMITFILES)
	@echo !!! Final submission prepared, test files included... READY FOR GRADING !!!

# make partialsubmit.tar.gz - cleans, creates tarball
# omitting test files
PARTIAL_SUBMITFILES=$(filter-out $(wildcard test*.txt), $(FULL_SUBMITFILES))
$(PARTIAL_SUBMITFILE): $(PARTIAL_SUBMITFILES)
	rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(UNGRADED_SUBMITFILE)
	COPYFILE_DISABLE=true tar --exclude=$(EXCLUDE_FILES) -vczf $(PARTIAL_SUBMITFILE) \
      $(PARTIAL_SUBMITFILES)
	@echo !!! WARNING: No test files included. Use 'make fullsubmit' to include test files. !!!

# make ungraded.tar.gz - cleans, creates tarball omitting test files, Makefile
UNGRADED_SUBMITFILES=$(filter-out Makefile, $(PARTIAL_SUBMITFILES))
$(UNGRADED_SUBMITFILE): $(UNGRADED_SUBMITFILES)
	rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(UNGRADED_SUBMITFILE)
	@touch __ungraded
	COPYFILE_DISABLE=true tar --exclude=$(EXCLUDE_FILES) -vczf $(UNGRADED_SUBMITFILE) \
      $(UNGRADED_SUBMITFILES) __ungraded
	@rm -f __ungraded
	@echo !!! WARNING: This submission will not be graded. !!!

# shortcut for make submit tarballs
fullsubmit: identifier $(FULL_SUBMITFILE)
partialsubmit: identifier $(PARTIAL_SUBMITFILE)
ungraded: identifier $(UNGRADED_SUBMITFILE)
.PHONY: fullsubmit partialsubmit ungraded

# REMOTE_PATH has default definition above
sync2caen:
ifeq ($(UNIQNAME), youruniqname)
	@echo Edit UNIQNAME variable in Makefile.
	@exit 1;
endif
	# Synchronize local files into target directory on CAEN
	rsync \
      -av \
      --delete \
      --exclude '*.o' \
      --exclude '$(EXECUTABLE)' \
      --exclude '$(EXECUTABLE)_debug' \
      --exclude '$(EXECUTABLE)_valgrind' \
      --exclude '$(EXECUTABLE)_profile' \
      --exclude '.git*' \
      --exclude '.vs*' \
      --exclude '*.code-workspace' \
      --filter=":- .gitignore" \
      "."/ \
      "$(UNIQNAME)@login.engin.umich.edu:$(REMOTE_PATH)/"
	echo "Files synced to CAEN at ~/$(REMOTE_PATH)/"
.PHONY: sync2caen

define MAKEFILE_HELP
EECS281 Advanced Makefile Help
* This Makefile uses advanced techniques, for more information:
    $$ man make

* General usage
    1. Follow directions at each "TODO" in this file.
       a. Set EXECUTABLE equal to the name from the project specification.
       b. Set PROJECTFILE equal to the name of the source file with main()
       c. Add any dependency rules specific to your files.
    2. Build, test, submit... repeat as necessary.

* Preparing submissions
    A) To build 'partialsubmit.tar.gz', a tarball without tests used to
       find buggy solutions in the autograder.

           *** USE THIS ONLY FOR TESTING YOUR SOLUTION! ***

       This is useful for faster autograder runs during development and
       free submissions if the project does not build.
           $$ make partialsubmit
    B) Build 'fullsubmit.tar.gz' a tarball complete with autograder test
       files.

           *** ALWAYS USE THIS FOR FINAL GRADING! ***

       It is also useful when trying to find buggy solutions in the
       autograder.
           $$ make fullsubmit

* Unit testing support
    A) Source files for unit testing should be named test*.cpp.  Examples
       include test_input.cpp or test3.cpp.
    B) Automatic build rules are generated to support the following:
           $$ make test_input
           $$ make test3
           $$ make alltests        (this builds all test drivers)
    C) If test drivers need special dependencies, they must be added
       manually.
    D) IMPORTANT: NO SOURCE FILES WITH NAMES THAT BEGIN WITH test WILL BE
       ADDED TO ANY SUBMISSION TARBALLS.

* Static Analysis support
    A) Matches current autograder style grading tests
    B) Usage:
           $$ make static

* Sync to CAEN support
    A) Requires an .ssh/config file with a login.engin.umich.edu host
       defined, SSH Multiplexing enabled, and an open SSH connection.
    B) Edit the REMOTE_BASEDIR variable if default is not preferred.
    C) Usage:
           $$ make sync2caen
endef
export MAKEFILE_HELP

help:
	@echo "$$MAKEFILE_HELP"
.PHONY: help

#######################
# TODO (begin) #
#######################
# individual dependencies for objects
# Examples:
# "Add a header file dependency"
# project2.o: project2.cpp project2.h
#
# "Add multiple headers and a separate class"
# HEADERS = some.h special.h header.h files.h
# myclass.o: myclass.cpp myclass.h $(HEADERS)
# project5.o: project5.cpp myclass.o $(HEADERS)
#
# SOME EXAMPLES
#
#test_thing: test_thing.cpp class.o functions.o
#class.o: class.cpp class.h
#functions.o: functions.cpp functions.h
#project0.o: project0.cpp class.h functions.h
#
# THE COMPILER CAN GENERATE DEPENDENCIES FROM SOURCE CODE
#
# % g++ -std=c++17 -MM *.cpp
#
# ADD YOUR OWN DEPENDENCIES HERE

######################
# TODO (end) #
######################
