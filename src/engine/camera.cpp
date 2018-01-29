#include "engine/camera.hpp"

#include <cmath>

static constexpr float deg2rad(float deg) {
    return deg * 180 / M_PI;
}

namespace eng {
	void camera::step(float distance, bool forward) {
	    const geo::vector diff = 
	    	geo::normalize(lookat - position) * distance;
	    position = position + ((forward) ? (diff) : (diff * -1));
	    lookat = lookat + ((forward) ? (diff) : (diff * -1));
	}

	void camera::xturn(float angle) {
		const geo::vector diff = lookat - position;
	    const float sx = diff.x * cos(angle) + diff.z * sin(angle);
	    const float sz = -diff.x * sin(angle) + diff.z * cos(angle);
	    lookat = position + geo::vector(sx, diff.y, sz);
	}

	void camera::yturn(float angle) {
		constexpr const float max_diff = 1.2F;

	    if (lookat.y > position.y + max_diff && angle > 0)
	        return;

	    if (lookat.y < position.y - max_diff && angle < 0)
	        return;

	    const float prev = geo::length(lookat - position);
	    lookat.y += angle;
	    const float setback = geo::length(lookat - position) - prev;
	    step(setback, false);
	}

	geo::matrix camera::view() const {
	    geo::vector w = geo::normalize(position - lookat);
	    geo::vector u = geo::normalize(geo::cross(up, w));
	    geo::vector v = geo::cross(w, u);

	    return geo::translation(-position.x, -position.y, -position.z) *
	           geo::matrix(u.x, v.x, w.x, 0,
	            	       u.y, v.y, w.y, 0,
	            	       u.z, v.z, w.z, 0,
	            	       0,   0,   0,   1);
	}

	geo::matrix camera::projection() const {
	    const float f = deg2rad(fov);
	    const float a = 1 / (tan(f / 2) * aspect_ratio);
	    const float b = 1 / tan(f / 2);
	    const float c = -(near_limit + far_limit) / (far_limit - near_limit);
	    const float d = -2 * near_limit * far_limit / (far_limit - near_limit);

	    return geo::matrix(a, 0, 0,  0,
	                	   0, b, 0,  0,
	                	   0, 0, c, -1,
	                	   0, 0, d,  1);
	}
}