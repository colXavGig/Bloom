ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	RM = del /s /q
	MKDIR = mkdir
	CP = copy
	FIXPATH = $(subst /,\,$1)
else
	detected_OS := $(shell uname -s)
	RM = rm -r
	MKDIR = mkdir -p
	CP = cp
	FIXPATH = $1
endif

# Paths
root := ./app
build := $(root)/build
bin := main.exe

# Compiler
CXX := g++
CXXFLAGS := -Wall -std=c++17 "-IC:/mingw64/include" 
LDFLAGS := -L"C:/mingw64/lib/MT" -lssl -lcrypto 

# Object files
obj_POD := FOS_METADATA.o FOS_FILE_S.o
obj_GardenManipulation := FileWriter.o FileBuilder.o Navigation.o
obj_paths := GardenPath.o

obj_filesystem := \
	$(root)/fileSystemManagement/build/Index.o \
	$(root)/fileSystemManagement/build/GardenTag.o \
	$(root)/fileSystemManagement/build/GardenProtocol.o \
	$(root)/fileSystemManagement/build/HashTree.o \
	$(root)/fileSystemManagement/build/HashNode.o \
	$(root)/fileSystemManagement/build/Index_c_api.o \
	$(root)/fileSystemManagement/build/GardenTag_c_api.o \
	$(root)/fileSystemManagement/build/Hashing.o \
	$(root)/fileSystemManagement/build/HashVector.o \
	$(root)/fileSystemManagement/build/StaticPath.o

# Submodules
SUBDIRS := app/fileSystemManagement

.PHONY: all $(SUBDIRS) clean

all: $(SUBDIRS) $(bin)

$(SUBDIRS):
	$(MAKE) -C $@

# Build the final executable
$(bin): $(obj_filesystem) $(addprefix $(build)/, main.o $(obj_POD) $(obj_GardenManipulation) $(obj_paths))
	@echo Detected OS: $(detected_OS)
	$(CXX) $^ -o $@ $(LDFLAGS)


# TODO: delete if not used
#	$(build)/filebuilder/FileBuilder.o  

##===============================================================================##
##			                   algo folder     									 ##
##===============================================================================##
$(build)/FOS_FILE_S.o: $(root)/FOS/FILE_S.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/FOS_METADATA.o: $(root)/FOS/FOS_metadata.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

DIFF.o: $(call FIXPATH, $(root)/algo/Diff.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/algo/Diff.cpp) -o $(call FIXPATH,$(build)/DIFF.o)
	@echo

JUXTAPOSE.o: $(root)/algo/Juxtapose.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/algo/Juxtapose.cpp) -o $(call FIXPATH,$(build)/JUXTAPOSE.o)
	@echo


##===============================================================================
##			                   GardenManipulation
##===============================================================================
$(build)/FileWriter.o: $(root)/fileSystemWriter/FileWriter.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(build)/FileBuilder.o: $(root)/fileSystemBuilder/fileBuilder.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/Navigation.o: $(root)/GardenNavigation/Navigation.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


##===============================================================================
##			                   path
##===============================================================================
$(build)/GardenPath.o: $(root)/paths/GardenPath.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/main.o: $(root)/main.cpp
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: all
	./main.exe
# Clean build directory

clean:
	$(RM) $(call FIXPATH, $(build)/**/*.o)
	$(RM) $(call FIXPATH, $(build)/*.o)
	$(RM) $(call FIXPATH, *.exe)
	#del /s /q build\*.o 2>nul
	#for /d %%D in $(build)\* do @rmdir /s /q "%%D" 2>nul