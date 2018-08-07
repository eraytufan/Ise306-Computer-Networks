CXX := g++
CXXFLAGS := -std=c++11
TARGET := out
DIST := catch.hpp makefile *.cpp *.h
DIST_NAME := Eray Tufan

$(TARGET): socket.o sha1.o
	$(CXX) -o $(TARGET) $^

.PHONY clean:
	rm -f *.o $(TARGET)

dist: clean
	mkdir -p $(DIST_NAME)
	cp $(DIST) $(DIST_NAME)
	tar czvf $(DIST_NAME).tar.gz $(DIST_NAME)
	rm $(DIST_NAME)/*
	rmdir $(DIST_NAME)
