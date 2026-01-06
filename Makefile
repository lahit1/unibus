CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC -I include
LDFLAGS = -shared

SRCS = $(shell find lib/ -type f -name "*.cxx")
OBJS = $(patsubst lib/%.cxx,build/%.o,$(SRCS))

TARGET = bin/libunibus.so

# obj dizinlerini oluştur
OBJDIRS := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(OBJDIRS))
$(shell mkdir -p $(dir $(TARGET)))

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p bin
	$(CXX) $(LDFLAGS) -o $@ $^

build/%.o: lib/%.cxx
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj/* $(TARGET)

