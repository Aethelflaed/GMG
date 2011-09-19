include Makefile.tools

#Defines special targets
.PHONY: gen, clean, mrproper, all, checkdirs

SRC_DIR := src
SRC_DIR += $(addprefix src/, $(MODULES))
BUILD_DIR := build
BUILD_DIR += $(addprefix build/, $(MODULES))
GEN_DIR := gen
GEN_DIR += $(addprefix gen/, $(MODULES))

SRC := $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
SRC += $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.ypp))
SRC += $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.l))
GEN := $(patsubst src/%.ypp, gen/%.cpp, $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.ypp)))
GEN += $(patsubst src/%.l, gen/%.c,     $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.l)))
OBJ := $(patsubst src/%.cpp, build/%.o, $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp)))

INCLUDES += -iquote gen -iquote src

GEN_OBJ := $(patsubst src/%.l, build/%.o, $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.l)))
GEN_OBJ += $(patsubst src/%.ypp, build/%.o, $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.ypp)))

vpath %.cpp $(SRC_DIR)
vpath %.l $(SRC_DIR)
vpath %.ypp $(SRC_DIR)

EXEC_NAME := $(EXEC) $(VERSION)
ifeq ($(TARGET), macos)
	EXEC_NAME := $(EXEC)
	BUNDLE_NAME := $(EXEC) $(VERSION).app
endif

define make-build-goal
$1/%.o: %.cpp
	$(CXX) -c $$< -o $$@ $(CXXFLAGS) $(INCLUDES) 
$1/%.o: %.c
	$(C) -c $$< -o $$@ $(CFLAGS) $(INCLUDES) 
endef

define make-gen-goal
$1/%.c: %.l
	$(LEX) $(LEXFLAGS) -o $$@ $$^
$1/%.cpp: %.ypp
	$(YACC) $(YACCFLAGS) $$^ -o $$@
endef

#Build all
all: checkdirs $(GEN_OBJ) $(OBJ)
	$(LD) $(GEN_OBJ) $(OBJ) -o "bin/$(EXEC_NAME)" $(LDFLAGS) $(INCLUDES) $(LIBRARIES)
	$(ECHO) "\nBinary generated in bin/"

#Generate object files from generated files
$(GEN_OBJ): $(GEN)
	$(foreach gen, $(patsubst gen/%.cpp, build/%.o, $(foreach gdir, $(GEN_DIR), $(wildcard $(gdir)/*.cpp))), $(CXX) -c $(patsubst build/%.o, gen/%.cpp, $(gen)) -o $(gen) $(CXXFLAGS) $(INCLUDES))
	$(foreach gen, $(patsubst gen/%.c, build/%.o, $(foreach gdir, $(GEN_DIR), $(wildcard $(gdir)/*.c))), $(C) -c $(patsubst build/%.o, gen/%.c, $(gen)) -o $(gen) $(CFLAGS) $(INCLUDES))
	
#Check for directories existences
checkdirs:
	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(GEN_DIR)
	$(MKDIR) bin

#Clean temporary object files
clean:
	$(RM) build/*

#Clean all except sources
mrproper: clean
	$(RM) bin/*
	$(RM) gen/*

#Build implicit rules for building all files
$(foreach gdir, $(GEN_DIR),   $(eval $(call make-gen-goal, $(gdir))))
$(foreach bdir, $(BUILD_DIR), $(eval $(call make-build-goal, $(bdir))))

