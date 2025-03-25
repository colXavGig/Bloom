ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	RM = del /s /q
	MKDIR = mkdir
	CP = copy
	FIXPATH = $(subst /,\,$1)
else
	detected_OS := $(shell uname -s)
	RM = rm -rf
	MKDIR = mkdir -p
	CP = cp
	FIXPATH = $1
endif

# Compiler settings
root=../app
build=$(root)/build
objects=Hashing.o StringVector.o HashNode.o HashTree.o FileWriter.o main.o

all: main.exe
	@echo Detected OS: $(detected_OS)
	
	
main.exe:Hashing.o StringVector.o HashNode.o HashTree.o FileWriter.o main.o

	@echo "making executable...\n";
	g++ $(build)/main.o \
	$(build)/datacollection/HashTree.o \
	$(build)/datacollection/HashNode.o \
	$(build)/datacollection/StringVector.o \
	$(build)/filewriter/FileWriter.o  \
	$(build)/hashing/Hashing.o \
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

FileWriter.o: $(call FIXPATH,$(root)/fileWriter/fileWriter.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/fileWriter/fileWriter.cpp) -o $(call FIXPATH,$(build)/filewriter/FileWriter.o)
	@echo

main.o: $(call FIXPATH,$(root)/main.cpp)
	@echo "making $@..."
	g++ -c $(call FIXPATH,$(root)/main.cpp) -o $(call FIXPATH,$(build)/main.o)
	@echo

run: all
	./main.exe
# Clean build directory

clean:
	del /s /q build\*.o 2>nul
	for /d %%D in $(build)\* do @rmdir /s /q "%%D" 2>nul
