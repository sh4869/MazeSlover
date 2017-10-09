CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers  -lc -lm -lnosys -lgcc -lrdimon -lstdc++
COMPILER  = g++
LIBS      =
LDFLAGS   =
TARGET    = build/mazeslover
INCLUDES  = \
-IInc
SRCDIR    = Src
SOURCES   = $(wildcard $(SRCDIR)/*.cpp) \
main.cpp
OBJDIR    = ./build
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<
$(OBJDIR)/%.o: main.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<


all: clean $(TARGET)
clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
-include $(DEPENDS)