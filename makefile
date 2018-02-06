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

BLD=`tput bold`
RED=`tput setaf 1`
GRN=`tput setaf 2`
YLW=`tput setaf 3`
BLU=`tput setaf 5`
TEL=`tput setaf 6`
WHT=`tput setaf 6`
NRM=`tput sgr0`

.PHONY: all, clean

all: $(BINARY)

test: $(BINARY)
	@printf "%s[ Tests ]%s $(BINARY)\n" "$(BLD)$(WHT)" $(NRM)
	@$(BINARY)

loc:
	@printf "%s[ Lines ]%s " "$(BLD)$(YLW)" $(NRM)
	@cat src/*pp src/geometry/* | wc -l

$(BINARY): $(OBJECTS)
	@mkdir -p bin
	@printf "%s[Linking]%s $@\n" "$(BLD)$(TEL)" $(NRM)
	@$(CXX) $(OBJECTS) -o $(BINARY) $(LDFLAGS)
	@printf "%s[ Strip ]%s $@\n" "$(BLD)$(TEL)" $(NRM)
	@strip $(BINARY)
	@printf "%s[Success] Build Succeeded!%s\n" "$(BLD)$(GRN)" $(NRM)

obj/%.o: src/%.cpp
	@mkdir -p obj
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/engine/%.o: src/engine/%.cpp
	@mkdir -p obj/engine
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/geometry/%.o: src/geometry/%.cpp
	@mkdir -p obj/geometry
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/objects/%.o: src/objects/%.cpp
	@mkdir -p obj/objects
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "%s[ Clean ]%s bin\n" "$(BLD)$(RED)" $(NRM)
	@rm -rf bin
	@printf "%s[ Clean ]%s obj\n" "$(BLD)$(RED)" $(NRM)
	@rm -rf obj
