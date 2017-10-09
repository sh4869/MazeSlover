CFLAGS    = -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -std=c++14 -lstdc++
COMPILER  = g++
CC        = g++
CXX       = g++
LIBS      =
LDFLAGS   =
TARGET    = build/mazeslover
INCLUDE  = \
-IInc
SRCDIR    = Src
SOURCES   = $(wildcard $(SRCDIR)/*.cpp) \
main.cpp
OBJDIR    = ./build
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)
.DEFAULT_GOAL := $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<
$(OBJDIR)/%.o: ./main.cpp Makefile
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)
run: 
	$(TARGET).exe
clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
	-rm -rf build
	-mkdir $(OBJDIR)

-include $(DEPENDS)