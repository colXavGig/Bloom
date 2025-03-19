# Compiler settings

all: 
#Hashing
	g++ -c processes/hashing.cpp -o build/hashing/Hashing.o
 
#datacollection
#vector
	g++ -c datacollection/dynamicarray/Vector.cpp -o build/datacollection/stringVector.o
#hashtree
	g++ -c datacollection/hashTree/HashNode.cpp -o build/datacollection/HashNode.o
	g++ -c datacollection/hashTree/HashTree.cpp -o build/datacollection/HashTree.o

#fileWriter
	g++ -c fileWriter/fileWriter.cpp -o build/filewriter/filewriter.o
 
	g++ -c main.cpp -o build/main.o


	g++ build/main.o build/datacollection/HashTree.o build/datacollection/HashNode.o \
	build/datacollection/stringVector.o \
	build/fileWriter/fileWriter.o  \
	build/hashing/Hashing.o \
	-Wall -I"C:/mingw64/include" -L"C:/mingw64/lib/MT" -lssl -lcrypto -o main.exe
# Clean build directory
clean:
	del /s /q build\*.o 2>nul
	for /d %%D in (build\*) do @rmdir /s /q "%%D" 2>nul