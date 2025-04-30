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

# Compiler settings
root=./app
build=$(root)/build
CXX := g++
CXXFLAGS := -Wall -I"C:/mingw64/include" -I"C:/dev/curl-8.13.0_2-win64-mingw/include"
LDFLAGS := -L"C:/mingw64/lib/MT" -L"C:/dev/curl-8.13.0_2-win64-mingw/lib" -lssl -lcrypto -lcurl
#folder objects
obj_algo := DIFF.o JUXTAPOSE.o

objet_POD:= FOS_METADATA.o FOS_FILE_S.o

obj_dataCollection := StringVector.o HashNode.o HashTree.o

obj_GardenManipulation := FileWriter.o FileBuilder.o Navigation.o GardenProtocol.o

obj_garden_tags := GardenTag.o

obj_paths := GardenPath.o 

obj_process := Hashing.o 

bin := main.exe

all: main.exe
## $(obj_dataCollection)
##$(build)/DIFF.o 
##$(build)/JUXTAPOSE.o 
main.exe: $(obj_GardenManipulation)  $(obj_garden_tags) $(obj_paths) $(obj_process) $(objet_POD) Index.o main.o

	@echo Detected OS: $(detected_OS)
	g++ $(build)/main.o \
	$(build)/FOS_FILE_S.o \
	$(build)/FOS_METADATA.o \
	$(build)/HashTree.o \
	$(build)/HashNode.o \
	$(build)/StringVector.o \
	$(build)/FileWriter.o  \
	$(build)/FileBuilder.o  \
	$(build)/Navigation.o  \
	$(build)/GardenProtocol.o \
	$(build)/Hashing.o \
	$(build)/GardenPath.o \
	$(build)/GardenTag.o \
	$(build)/Index.o \
	-Wall \
	-I"C:/mingw64/include" \
	-I"C:/dev/curl-8.13.0_2-win64-mingw/include" \
	-L"C:/mingw64/lib/MT" \
	-L"C:/dev/curl-8.13.0_2-win64-mingw/lib" \
	-lssl -lcrypto  \
	-o main.exe


# TODO: delete if not used
#	$(build)/filebuilder/FileBuilder.o  

##===============================================================================##
##			                   algo folder     									 ##
##===============================================================================##
FOS_FILE_S.o: $(call FIXPATH,$(root)/FOS/FILE_S.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/FOS/FILE_S.cpp) -o $(call FIXPATH,$(build)/FOS_FILE_S.o)
	@echo

FOS_METADATA.o: $(call FIXPATH, $(root)/FOS/FOS_metadata.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/FOS/FOS_metadata.cpp) -o $(call FIXPATH,$(build)/FOS_METADATA.o)
	@echo

DIFF.o: $(call FIXPATH, $(root)/algo/Diff.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/algo/Diff.cpp) -o $(call FIXPATH,$(build)/DIFF.o)
	@echo

JUXTAPOSE.o: $(root)/algo/Juxtapose.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/algo/Juxtapose.cpp) -o $(call FIXPATH,$(build)/JUXTAPOSE.o)
	@echo
##===============================================================================##
##			                   data collection									 ##
##===============================================================================##
StringVector.o: $(root)/datacollection/dynamicarray/Vector.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/datacollection/dynamicarray/Vector.cpp) -o $(call FIXPATH,$(build)/StringVector.o)
	@echo

HashNode.o: $(root)/datacollection/hashTree/HashNode.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/datacollection/hashTree/HashNode.cpp) -o $(call FIXPATH,$(build)/HashNode.o)
	@echo

HashTree.o: $(root)/datacollection/hashTree/HashTree.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/datacollection/hashTree/HashTree.cpp) -o $(call FIXPATH,$(build)/HashTree.o)
	@echo


##===============================================================================
##			                   GardenManipulation
##===============================================================================
FileWriter.o: $(call FIXPATH,$(root)/fileSystemWriter/FileWriter.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileSystemWriter/FileWriter.cpp) -o $(call FIXPATH,$(build)/FileWriter.o)
	@echo
	
FileBuilder.o: $(call FIXPATH,$(root)/fileSystemBuilder/fileBuilder.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileSystemBuilder/fileBuilder.cpp) -o $(call FIXPATH,$(build)/FileBuilder.o)
	@echo

Navigation.o: $(call FIXPATH,$(root)/GardenNavigation/Navigation.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/GardenNavigation/Navigation.cpp) -o $(call FIXPATH,$(build)/Navigation.o)
	@echo

GardenProtocol.o: $(call FIXPATH,$(root)/GardenProtocol/GardenProtocol.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/GardenProtocol/GardenProtocol.cpp) -o $(call FIXPATH,$(build)/GardenProtocol.o)
	@echo
##===============================================================================
##			                   path
##===============================================================================
GardenPath.o: $(call FIXPATH, $(root)/paths/GardenPath.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/paths/GardenPath.cpp) -o $(call FIXPATH, $(build)/GardenPath.o)
	@echo

##===============================================================================
##			                   garden tags
##===============================================================================
GardenTag.o: $(call FIXPATH,$(root)/garden_tags/GardenTag.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/garden_tags/GardenTag.cpp) -o $(call FIXPATH,$(build)/GardenTag.o)
	@echo

##===============================================================================
##			                   processes
##===============================================================================
Hashing.o: $(call FIXPATH, $(root)/processes/Hashing.cpp)
	@echo "making $@...\n";
	g++ -c $(call FIXPATH, $(root)/processes/Hashing.cpp) -o $(call FIXPATH, $(build)/Hashing.o)
	@echo

Index.o: $(call FIXPATH, $(root)/index/Index.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/index/Index.cpp) -o $(call FIXPATH, $(build)/$@)
	@echo

main.o: $(call FIXPATH,$(root)/main.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/main.cpp) -o $(call FIXPATH,$(build)/main.o)
	@echo


run: all
	./main.exe
# Clean build directory

clean:
	$(RM) $(call FIXPATH, $(build)/**/*.o)
	$(RM) $(call FIXPATH, $(build)/*.o)
	$(RM) $(call FIXPATH, *.exe)
	#del /s /q build\*.o 2>nul
	#for /d %%D in $(build)\* do @rmdir /s /q "%%D" 2>nul