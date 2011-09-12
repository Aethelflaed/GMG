include Makefile.tools

#Defines special targets
.PHONY: clean, mrproper, all, checkdirs, bin, lib, lib_target, exec_target, test, test_target

ifeq ($(OS), macos)
	CXX := /usr/local/bin/x86_64-apple-darwin10.7.0-g++
else
	CXX := g++
endif
ifeq ($(OS), win32)
	CXX := mingw32-g++
endif

LD = $(CXX)

CXXFLAGS := -std=c++0x

SRC_DIR := $(addprefix src/, $(MODULES))
SRC_DIR += src
BUILD_DIR := $(addprefix build/, $(MODULES))
BUILD_DIR += build

SRC := $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))

SRCLIB_DIR := $(addprefix lib/src/, $(LIB_MODULES))
SRCLIB_DIR += lib/src
BUILDLIB_DIR := $(addprefix build/__lib/, $(LIB_MODULES))
BUILDLIB_DIR += build/__lib

LIBSRC := $(foreach sldir, $(SRCLIB_DIR), $(wildcard $(sldir)/*.cpp))
LIBOBJ := $(patsubst lib/src/%.cpp, build/__lib/%.o, $(LIBSRC))

SRCTEST_DIR := $(addprefix testing/, $(TEST_MODULES))
SRCTEST_DIR += testing
BUILDTEST_DIR := $(addprefix build/__testing/, $(TEST_MODULES))
BUILDTEST_DIR += build/__testing

TESTSRC := $(foreach stdir, $(SRCTEST_DIR), $(wildcard $(stdir)/*.cpp))
TESTOBJ := $(patsubst testing/%.cpp, build/__testing/%.o, $(TESTSRC))

vpath %.cpp $(SRC_DIR)
vpath %.cpp $(SRCLIB_DIR)
vpath %.cpp $(SRCTEST_DIR)

EXEC_NAME := $(EXEC) $(VERSION)
BUNDLE_NAME := $(EXEC) $(VERSION).app
ifeq ($(OS), win32)
	EXEC_NAME := $(EXEC) $(VERSION).exe
endif
ifeq ($(OS), win64)
	EXEC_NAME := $(EXEC) $(VERSION).exe
endif
ifeq ($(OS), macos)
	EXEC_NAME := $(EXEC)
	BUNDLE_NAME := $(EXEC) $(VERSION).app
endif

LIB_NAME := lib$(LIB).so
ifeq ($(OS), win32)
	LIB_NAME := $(LIB).dll
endif
ifeq ($(OS), win64)
	LIB_NAME := $(LIB).dll
endif

TEST_NAME := $(TEST)
ifeq ($(OS), win32)
	TEST_NAME := $(TEST).exe
endif
ifeq ($(OS), win64)
	TEST_NAME := $(TEST).exe
endif

define make-goal
$1/%.o: %.cpp
	$(CXX) -c $$< -o $$@ $(CXXFLAGS) $(INCLUDES) 
endef

#Build all
all: checkdirs lib_target exec_target test_target
	$(ECHO) "\nBinary generated in bin/"

exec_target: $(OBJ)
	$(LD) $^ -o "bin/$(EXEC_NAME)" $(LDFLAGS) $(INCLUDES) $(LIBRARIES)

lib: checkdirs lib_target

lib_target: $(LIBOBJ)
	$(CXX) --shared $^ -o "bin/$(LIB_NAME)" $(CXXFLAGS) $(INCLUDES) $(LIBRARIES)

test: checkdirs test_target

test_target: $(TESTOBJ)
	$(LD) $^ -o "bin/$(TEST_NAME)" $(LDFLAGS) $(INCLUDES) $(LIBRARIES) -lunit++

#Check for directories existences
checkdirs: $(BUILD_DIR) $(BUILDLIB_DIR) $(BUILDTEST_DIR) bin

$(BUILD_DIR):
	$(MKDIR) $@

$(BUILDLIB_DIR):
	$(MKDIR) $@

$(BUILDTEST_DIR):
	$(MKDIR) $@

bin:
	$(MKDIR) $@

#Clean temporary object files
clean:
	$(RM) build/*

#Clean all except sources
mrproper: clean
	$(RM) bin/*

#Build implicit rules for building all files
$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))
$(foreach lbdir, $(BUILDLIB_DIR), $(eval $(call make-goal, $(lbdir))))
$(foreach tbdir, $(BUILDTEST_DIR), $(eval $(call make-goal, $(tbdir))))

