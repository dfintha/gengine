#if !defined(GENGINE_OBJECTS_OBJECTS)
#define GENGINE_OBJECTS_OBJECTS

#include "engine/scene.hpp"
#include "engine/texture.hpp"
#include "geometry/vector.hpp"
#include <string>

namespace obj {
	struct vertex_data {
		geo::vector position;
		geo::vector normal;
		float u, v;

		vertex_data() : position(), normal(), u(0), v(0) { }
		vertex_data(const vertex_data&) = default;
		vertex_data(vertex_data&&) = default;
		vertex_data& operator=(const vertex_data&) = default;
		vertex_data& operator=(vertex_data&&) = default;
		~vertex_data() noexcept = default;
	};

	enum draw_mode_t {
		polyfill, polywire
	};

	enum draw_side_t  {
		inside, outside
	};

	class object_base {
	protected:
		unsigned vao, vbo;
	    size_t vertices;
	    vertex_data *data;

	public:
		float angle;
		float shine;
		geo::vector position;
		geo::vector rotation;
		geo::vector scale;
		geo::vector diffuse;
		geo::vector specular;
		geo::vector ambient;
		draw_side_t draw_side;
		draw_mode_t draw_mode;
		bool textured;
		eng::texture_ptr texture;

		object_base() :
	        vao(0),
	        vbo(0),
	        vertices(0),
	        data(nullptr),
	        angle(0),
	        shine(100),
	        position(),
	        rotation(),
	        scale(1, 1, 1, 1),
	        diffuse(0.5F, 0.5F, 0.5F),
	        specular(0.8F, 0.8F, 0.8F),
	        ambient(0.3F, 0.3F, 0.3F),
	        draw_side(outside),
	        draw_mode(polyfill),
	        textured(false),
	        texture(nullptr)
	    { }

	    object_base(const object_base&) = default;
		object_base(object_base&&) = default;
		object_base& operator=(const object_base&) = default;
		object_base& operator=(object_base&&) = default;

		virtual ~object_base() noexcept {
			if (data != nullptr)
        		delete[] data;
		};

		void draw(const eng::scene& scene) const;

		virtual void create() = 0;
		virtual vertex_data vertex_at(float u, float v) const;
	};


	class sphere : public object_base {
	public:
	    void create() override;
	    vertex_data vertex_at(float u, float v) const override;
	};

	class rectangle : public object_base {
	public:
	    void create() override;
	};

	class cylinder : public object_base {
	public:
	    void create() override;
	};

	class obj_model : public object_base {
		std::string file;
	public:
		obj_model(const char *file);
	    void create() override;
	};
}

#endif
