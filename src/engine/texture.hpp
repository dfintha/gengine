#if !defined(GENGINE_ENGINE_TEXTURE)
#define GENGINE_ENGINE_TEXTURE

#include <memory>

#include "geometry/vector.hpp"
#include "gl.hpp"

namespace eng {
	struct texture_base {
		unsigned id;

		texture_base();
		texture_base(const texture_base&) = default;
		texture_base(texture_base&&) = default;
		texture_base& operator=(const texture_base&) = default;
		texture_base& operator=(texture_base&&) = default;
		virtual ~texture_base() noexcept { }

		virtual void make() = 0;
	};

	template <unsigned S>
	struct texture : public texture_base {
	    geo::vector image[S][S];

	    texture() : texture_base() { }
	    texture(const texture&) = default;
		texture(texture&&) = default;
		texture& operator=(const texture&) = default;
		texture& operator=(texture&&) = default;
	    ~texture() noexcept = default;

	    void make() override {
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, S, S, 0, GL_RGBA, GL_FLOAT, image);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	};

	using texture_ptr = std::shared_ptr<texture_base>;
}

namespace tex {
	template <unsigned S>
	eng::texture_ptr checkerboard(const geo::vector& c1, const geo::vector& c2) {
		auto result = new eng::texture<S>;
		for (unsigned x = 0; x < S; ++x) {
			for (unsigned y = 0; y < S; ++y) {
				result->image[x][y] = (x % 2 == y % 2) ? c1 : c2;
			}
		}
		result->make();
		return eng::texture_ptr(result);
	}
	
	template <unsigned S>
	eng::texture_ptr hstripes(const geo::vector& c1, const geo::vector& c2) {
		auto result = new eng::texture<S>;
		for (unsigned x = 0; x < S; ++x) {
			for (unsigned y = 0; y < S; ++y) {
				result->image[x][y] = (y % 2 == 0) ? c1 : c2;
			}
		}
		result->make();
		return eng::texture_ptr(result);
	}

	template <unsigned S>
	eng::texture_ptr vstripes(const geo::vector& c1, const geo::vector& c2) {
		auto result = new eng::texture<S>;
		for (unsigned x = 0; x < S; ++x) {
			for (unsigned y = 0; y < S; ++y) {
				result->image[x][y] = (x % 2 == 0) ? c1 : c2;
			}
		}
		result->make();
		return eng::texture_ptr(result);
	}

	template <unsigned S>
	eng::texture_ptr randomized(const geo::vector& c1, const geo::vector& c2) {
		auto result = new eng::texture<S>;
		for (unsigned x = 0; x < S; ++x) {
			for (unsigned y = 0; y < S; ++y) {
				result->image[x][y] = (rand() % 2 == 0) ? c1 : c2;
			}
		}
		result->make();
		return eng::texture_ptr(result);
	}
}

#endif
