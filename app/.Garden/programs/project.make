# Compiler settings
CXX = g++
CXXFLAGS = -Wall -I"C:/mingw64/include" -L"C:/mingw64/lib/MT" -lssl_static -lcrypto_static

# Source files
SRCS = directory.cpp tree.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = garden_test2.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o