#include "engine/texture.hpp"
#include "gl.hpp"

namespace eng {
	texture_base::texture_base() : id(0) {
		glGenTextures(1, &id);
    	glBindTexture(GL_TEXTURE_2D, id);
	}
}
