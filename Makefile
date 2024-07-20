CXX = g++ -std=c++17
CXXFLAGS = -Wall -g -MMD -I include 
SOURCES = $(wildcard src/exchange/*.cpp) $(wildcard src/server/*.cpp)
CLIENT_SOURCES = $(wildcard src/client/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
CLIENT_OBJECTS = $(patsubst src/%.cpp, build/%.o, $(CLIENT_SOURCES))
DEPENDS = $(OBJECTS:.o=.d) $(CLIENT_OBJECTS:.o=.d)
EXEC = server
CLIENT_EXEC = client

all: server client

server: $(EXEC)

client: $(CLIENT_EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(CLIENT_EXEC): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o $(CLIENT_EXEC)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

-include $(DEPENDS)

.PHONY: all server client clean
clean:
	rm -rf build $(EXEC) $(CLIENT_EXEC)
