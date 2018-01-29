#if !defined(GENGINE_ENGINE_SHADER_PROGRAM)
#define GENGINE_ENGINE_SHADER_PROGRAM

#include "engine/shader.hpp"

namespace eng {
	struct shader_program {
		unsigned handle;
		shader vertex;
		shader fragment;
		bool finalized;

		bool make();
		void use() const;
		void dispose();

		inline operator unsigned() const {
	        return handle;
	    }
	};
}

#endif
