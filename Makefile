COMPILER  = g++
CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS =
else
  LDFLAGS =
endif
LIBS      =
INCLUDE   = -I./Inc
TARGET    = ./build/$(shell basename `readlink -f .`)

SOURCES   = main.cpp \
$(wildcard Src/*.cpp)

OBJDIR    = ./build
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

run:
	build/mazeslover

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)