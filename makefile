BINARY=bin/gengine
OBJECTS=obj/program.o 				\
		obj/engine/camera.o 		\
		obj/engine/shader.o 		\
		obj/engine/shader_program.o	\
		obj/engine/texture.o		\
		obj/geometry/vector.o 		\
		obj/geometry/matrix.o 		\
		obj/objects/cylinder.o 	    \
		obj/objects/rectangle.o 	\
		obj/objects/sphere.o 		\
		obj/objects/obj_model.o     \
		obj/objects/objects.o

CXX=clang++
CXXFLAGS=-std=c++14 -O2 -Wall -Wextra -Werror -pedantic -ffast-math -I./src
CXXFLAGS+=`pkg-config --cflags gl glew freeglut`
LDFLAGS=`pkg-config --libs gl glew freeglut`

.PHONY: all, clean

all: $(BINARY)

loc:
	@printf "[N] "
	@cat src/*pp src/geometry/* | wc -l

run: $(BINARY)
	@$(BINARY)

$(BINARY): $(OBJECTS)
	@mkdir -p bin
	@printf "[L] $@\n"
	@$(CXX) $(OBJECTS) -o $(BINARY) $(LDFLAGS)
	@printf "[S] $@\n"
	@strip $(BINARY)
	@printf "[+] Build Succeeded!%s\n"

obj/%.o: src/%.cpp
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/engine/%.o: src/engine/%.cpp
	@mkdir -p obj/engine
	@printf "[C] $<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/geometry/%.o: src/geometry/%.cpp
	@mkdir -p obj/geometry
	@printf "[C] $<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/objects/%.o: src/objects/%.cpp
	@mkdir -p obj/objects
	@printf "[C] $<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "[R] bin\n"
	@rm -rf bin
	@printf "[R] obj\n"
	@rm -rf obj

