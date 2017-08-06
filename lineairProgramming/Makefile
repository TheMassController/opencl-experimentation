#Compilers, etc
LD := g++
#Directories and files
SRCDIR:=./
INCDIR:=./
LIBDIR:=lib/
ODIR:=obj/
DEBUGODIR=obj_dbg/

CXXFILES:=$(wildcard $(SRCDIR)*.cpp)
OFILES= $(patsubst $(SRCDIR)%,$(ODIR)%,$(patsubst %.cpp,%.cpp.o,$(CXXFILES)))
DEBUGOFILES= $(patsubst $(SRCDIR)%,$(DEBUGODIR)%,$(patsubst %.cpp,%.cpp.o,$(CXXFILES)))

LIB=
TARGET:=final
DEBUGTARGET:=final_dbg

#compiling and linking options
LDFLAGS :=
LDRELEASEFLAGS := -s
LDDEBUGFLAGS :=

CXXFLAGS := -std=gnu++14 -I $(INCDIR) -Wall -Werror -Wfatal-errors -Wshadow -march=native -MP -MMD
CXXRELEASEFLAGS := -O3
CXXDEBUGFLAGS := -DDEBUG -ggdb -Og

.PHONY: all clean release debug

release: $(TARGET)

debug: $(DEBUGTARGET)

all: release debug

-include $(OFILES:%.o=%.d)
-include $(DEBUGOFILES:%.o=%.d)

$(ODIR) $(DEBUGODIR):
	@mkdir -p $@

$(ODIR)%.cpp.o: $(SRCDIR)/%.cpp | $(ODIR)
	$(CXX) $(CXXFLAGS) $(CXXRELEASEFLAGS) -o $@ -c $<

$(DEBUGODIR)%.cpp.o : $(SRCDIR)/%.cpp | $(DEBUGODIR)
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) -o $@ -c $<

$(TARGET): $(OFILES)
	$(LD) $(LDFLAGS) $(LDRELEASEFLAGS) -o $@ $^ $(LIB)

$(DEBUGTARGET) : $(DEBUGOFILES)
	$(LD) $(LDFLAGS) $(LDDEBUGFLAGS) -o $@ $^ $(LIB)

clean:
	@rm -rf $(ODIR)
	@rm -rf $(DEBUGODIR)
	@rm -f $(TARGET)
