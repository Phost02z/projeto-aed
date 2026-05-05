CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
SRCDIR   = src
SRCS     = $(wildcard $(SRCDIR)/*.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = ids

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
