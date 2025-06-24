# Compiler and flags
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2

# Directories
SRCDIR    := src
BINDIR    := bin

SRCS      := $(wildcard $(SRCDIR)/*.cpp)
BINS      := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(SRCS))

.PHONY: all clean

all: | $(BINDIR) $(BINS)

$(BINDIR)/%: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR)/*

print-%:
	@echo $* = $($*)
