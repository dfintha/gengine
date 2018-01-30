#include "engine/shader.hpp"
#include "gl.hpp"

#include <iostream>
#include <fstream>

namespace eng {
	bool shader::make(const char *source, unsigned type) {
		if (finalized)
			return false;

		category = type;

		std::ifstream stream;
	    stream.open(source);
	    if (stream.fail())
	        return false;

	    stream.seekg(0, std::ios::end);
	    const size_t length = stream.tellg();
	    stream.seekg(0, std::ios::beg);

	    char *buffer = new char[length + 1];
	    stream.read(buffer, length);
	    buffer[length] = '\0';
	    stream.close();

	    handle = glCreateShader(category);
	    if (handle == 0) {
	    	delete[] buffer;
	        return false;
	    }

	    finalized = true;
	    glShaderSource(handle, 1, const_cast<const char **>(&buffer), nullptr);
	    glCompileShader(handle);
	    delete[] buffer;

	    int ok;
    	glGetShaderiv(handle, GL_COMPILE_STATUS, &ok);

    	if (!ok) {
    		int length, written;
	        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	        buffer = new char[length];
	        glGetShaderInfoLog(handle, length, &written, buffer);
	        std::cerr << buffer << std::endl;
	        delete[] buffer;
	        return false;
    	}

    	return true;
	}
}
