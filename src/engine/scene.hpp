#if !defined(GENGINE_ENGINE_SCENE)
#define GENGINE_ENGINE_SCENE

#include "engine/camera.hpp"
#include "engine/shader_program.hpp"
#include "geometry/vector.hpp"
#include "gl.hpp"

namespace obj {
	class object_base;
}

#include <memory>
#include <vector>

namespace eng {
	struct scene {
		int width, height;
		bool grab_mouse;
		bool full_screen;
		eng::camera cam;
		eng::shader_program program;
		geo::vector light_position;
		geo::vector light_color;
		geo::vector ambient_color;
		geo::vector background_color;
		std::vector<std::shared_ptr<obj::object_base>> objects;

		scene() :
			width(1000),
			height(700),
			grab_mouse(false),
			full_screen(false),
			cam(),
			program(),
			light_position(),
			light_color(),
			ambient_color(),
			background_color(),
			objects()
		{ }

		scene(const scene&) = default;
	    scene(scene&&) = default;
	    scene& operator=(const scene&) = default;
	    scene& operator=(scene&&) = default;
	    ~scene() noexcept = default;

	    inline void toggle_full_screen() {
	    	if (full_screen) {
		        glutReshapeWindow(width, height);
		        glutPositionWindow(100, 100);
		    } else {
		        glutFullScreen();
		    }

		    full_screen = !full_screen;
	    }
	};
}

#endif
