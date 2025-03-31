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
objects := Hashing.o StringVector.o HashNode.o HashTree.o FileWriter.o FileIterator.o Growth.o GardenPath.o main.o
bin := main.exe

all: main.exe
	@echo Detected OS: $(detected_OS)

main.exe:Hashing.o StringVector.o HashNode.o HashTree.o FileWriter.o FileIterator.o Growth.o GardenPath.o main.o


	@echo "making executable...\n";
	g++ $(build)/main.o \
	$(build)/datacollection/HashTree.o \
	$(build)/datacollection/HashNode.o \
	$(build)/datacollection/StringVector.o \
	$(build)/filewriter/FileWriter.o  \
	$(build)/filereader/FileIterator.o  \
	$(build)/filebuilder/FileBuilder.o  \
	$(build)/hashing/Hashing.o \
	$(build)/growth/Growth.o \
	$(build)/GardenPath.o \
	-Wall -I"C:/mingw64/include" -L"C:/mingw64/lib/MT" -lssl -lcrypto -o main.exe



Hashing.o: $(call FIXPATH, $(root)/processes/Hashing.cpp)
	@echo "making $@...\n";
	g++ -c $(call FIXPATH, $(root)/processes/Hashing.cpp) -o $(call FIXPATH, $(build)/hashing/Hashing.o)
	@echo

#datacollection

StringVector.o: $(root)/datacollection/dynamicarray/Vector.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/datacollection/dynamicarray/Vector.cpp) -o $(call FIXPATH,$(build)/datacollection/StringVector.o)
	@echo

HashNode.o: $(call FIXPATH, $(root)/datacollection/hashTree/HashNode.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/datacollection/hashTree/HashNode.cpp) -o $(call FIXPATH,$(build)/datacollection/HashNode.o)
	@echo

HashTree.o: $(root)/datacollection/hashTree/HashTree.cpp
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/datacollection/hashTree/HashTree.cpp) -o $(call FIXPATH,$(build)/datacollection/HashTree.o)
	@echo

FileWriter.o: $(call FIXPATH,$(root)/fileWriter/FileWriter.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileWriter/FileWriter.cpp) -o $(call FIXPATH,$(build)/filewriter/FileWriter.o)
	@echo

FileIterator.o: $(call FIXPATH,$(root)/fileReader/FileIterator.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileReader/FileIterator.cpp) -o $(call FIXPATH,$(build)/filereader/FileIterator.o)
	@echo
	
Growth.o: $(call FIXPATH,$(root)/growth/Growth.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/growth/Growth.cpp) -o $(call FIXPATH,$(build)/growth/Growth.o)
	@echo	
	
FileBuilder.o: $(call FIXPATH,$(root)/fileReader/component/FileBuilder.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileReader/component/FileBuilder.cpp) -o $(call FIXPATH,$(build)/filebuilder/FileBuilder.o)
	@echo
	

main.o: $(call FIXPATH,$(root)/main.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/main.cpp) -o $(call FIXPATH,$(build)/main.o)
	@echo

GardenPath.o: $(call FIXPATH, $(root)/paths/GardenPath.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH, $(root)/paths/GardenPath.cpp) -o $(call FIXPATH, $(build)/GardenPath.o)
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
