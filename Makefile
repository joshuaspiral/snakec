CXX=g++
CXXFLAGS = -Wall -Wextra -ggdb -O3
LIBS = `pkg-config raylib --libs`
SRCS = main.cpp
TARGET = snake

make all: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $(TARGET) $(SRCS) -lm

clean:
	rm $(TARGET)
