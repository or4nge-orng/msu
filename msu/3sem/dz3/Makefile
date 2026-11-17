CXX = wg++
CXXFLAGS = -std=c++11 -fno-elide-constructors

TARGET = a.out
OBJS = main.o stack.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp stack.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

stack.o: stack.cpp stack.hpp
	$(CXX) $(CXXFLAGS) -c stack.cpp

clean:
	rm -f $(OBJS) $(TARGET)