CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I. $(shell pkg-config --cflags sdl2)
LDFLAGS  := $(shell pkg-config --libs sdl2)

BUILD_DIR := build
TARGET    := $(BUILD_DIR)/raytracer

# All .cpp files under the project (excluding build output)
SRCS := $(shell find . -name '*.cpp' -not -path './$(BUILD_DIR)/*')
OBJS := $(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
.PHONY: all clean

all: $(TARGET)

render: $(TARGET)
	./$(TARGET) test1.json > out.ppm

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: ./%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)