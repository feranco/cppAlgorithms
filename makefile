# compiler
CC=g++ -std=c++11

# compiler options (-g: turn on debugging; -Wall: turn on warnings -Werror: warning like errors)
CPPFLAGS=-g -Wall -Werror

# folders
SOURCEDIR=source
BUILDDIR=build

# source files
SOURCES:=$(shell find $(SOURCEDIR) -name '*.cpp')

# object files
OBJECTS:=$(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))

# binary file
EXECUTABLE:=tcpp

# utility generating detected dependencies (-MT: the target is exactly the following string)
MAKEDEPEND=$(CC) -M -MT $(BUILDDIR)/$*.o $(CPPFLAGS) -o $(BUILDDIR)/$*.d $<

# utility creating the build directory
MAKEDIR=mkdir -p $(BUILDDIR) $(@D)

all: $(EXECUTABLE)

# object files rule
$(BUILDDIR)/%.o: %.cpp
	@$(MAKEDIR)
	@$(MAKEDEPEND)
	$(CC) $(CPPFLAGS) -c $< -o $@

# binary file rule
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d)
