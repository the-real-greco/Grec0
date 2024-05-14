# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Directories
INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Create the necessary directories
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Source and object files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXECUTABLE = $(BINDIR)/Grec0

# Default target
all: $(EXECUTABLE)

# Link the object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCDIR) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
