SRCDIR := src
BINDIR := bin
OBJDIR := obj

CURPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
TARGET := $(BINDIR)/$(notdir $(patsubst %/, %, $(dir $(CURPATH))))

CPPFILES := $(wildcard $(SRCDIR)/*.cpp)
RCFILES := $(wildcard $(SRCDIR)/*.rc)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(CPPFILES)) $(patsubst $(SRCDIR)/%.rc, $(OBJDIR)/%.o, $(RCFILES))
DEPFILES := $(OBJFILES:.o=.d)

INCPATH :=
LIBPATH :=

CC := g++
RC := windres
CFLAGS := -c -Wall -std=c++11
LDFLAGS :=

all: $(CPPFILES) $(RCFILES) $(TARGET)

run: all
	start $(TARGET)

clean:
	rm -f $(OBJFILES) $(DEPFILES) $(TARGET).exe

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) $(LIBPATH) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(INCPATH) $(CFLAGS) -MMD $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.rc $(SRCDIR)/*.glsl
	$(RC) $< -o $@

-include $(DEPFILES)
