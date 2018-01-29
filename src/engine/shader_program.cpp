#include "engine/shader_program.hpp"
#include "gl.hpp"

namespace eng {
	bool shader_program::make() {
	    if (finalized)
	        return false;

	    handle = glCreateProgram();
	    if (handle == 0)
	        return false;

	    finalized = true;
	    glAttachShader(handle, vertex);
	    glAttachShader(handle, fragment);
	    glLinkProgram(handle);

	    int ok;
	    glGetProgramiv(handle, GL_LINK_STATUS, &ok);
	    return !!ok;
	}

	void shader_program::use() const {
	    glUseProgram(handle);
	}

	void shader_program::dispose() {
	    glDeleteProgram(handle);
	    handle = 0;
	    finalized = false;
	}
}
