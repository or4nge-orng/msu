CXX = g++
CXXFLAGS = -fno-elide-constructors -std=c++11

TARGET = a.out
OBJS = main.o CPoly.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp CPoly.h
	$(CXX) $(CXXFLAGS) -c main.cpp

CPoly.o: CPoly.cpp CPoly.h
	$(CXX) $(CXXFLAGS) -c CPoly.cpp

clean:
	rm -f $(OBJS) $(TARGET)