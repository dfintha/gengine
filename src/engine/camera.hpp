#if !defined(GENGINE_ENGINE_CAMERA)
#define GENGINE_ENGINE_CAMERA

#include "geometry/vector.hpp"
#include "geometry/matrix.hpp"

namespace eng {
	struct camera {
		geo::vector position;
    	geo::vector lookat;
    	geo::vector up;
    	float fov;
    	float aspect_ratio;
    	float near_limit;
    	float far_limit;

    	camera() :
	        position(0, 0, 0),
	        lookat(0, 0, 1),
	        up(0, -1, 0),
	        fov(120),
	        aspect_ratio(1),
	        near_limit(0.0001F),
	        far_limit(100)
	    { }

	    camera(const camera&) = default;
	    camera(camera&&) = default;
	    camera& operator=(const camera&) = default;
	    camera& operator=(camera&&) = default;
	    ~camera() noexcept = default;

	    void step(float distance, bool forward);
	    void xturn(float angle);
	    void yturn(float angle);

	    geo::matrix view() const;
	    geo::matrix projection() const;
	};
}

#endif
