#include "objects/objects.hpp"
#include "gl.hpp"

#include <cmath>

namespace obj {
	void sphere::create() {
		using voidptr = void *;
		constexpr float N = 128;
	    constexpr float M = 64;
	    vertices = N * M * 6;

	    glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    data = new vertex_data[vertices];
	    vertex_data *pointer = data;

	    for (int i = 0; i < N; ++i) {
	        for (int j = 0; j < M; ++j) {
	            *pointer++ = vertex_at(float(i) / N, float(j) / M);
	            *pointer++ = vertex_at(float(i + 1) / N, float(j) / M);
	            *pointer++ = vertex_at(float(i) / N, float(j + 1) / M);
	            *pointer++ = vertex_at(float(i + 1) / N, float(j) / M);
	            *pointer++ = vertex_at(float(i + 1) / N, float(j + 1) / M);
	            *pointer++ = vertex_at(float(i) / N, float(j + 1) / M);
	        }
	    }

	    if (draw_side == inside) {
	        for (size_t i = 0; i < vertices; ++i) {
	            data[i].normal = data[i].normal - data[i].normal * 2;
	        }
	    }

	    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(vertex_data),
	                 data, GL_STATIC_DRAW);

	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data),
	                          voidptr(offsetof(vertex_data, position)));

	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data),
	                          voidptr(offsetof(vertex_data, normal)));

	    glEnableVertexAttribArray(2);
	    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data),
	                          voidptr(offsetof(vertex_data, u)));

	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	    glBindVertexArray(0);
	}

	vertex_data sphere::vertex_at(float u, float v) const {
		vertex_data result;
		const geo::vector where =
			geo::vector(cosf(u * 2 * M_PI) * sinf(v * M_PI),
	                    sinf(u * 2 * M_PI) * sinf(v * M_PI) * -1,
	                    cos(v * M_PI));
		result.normal = geo::normalize(where);
	    result.position = result.normal;
	    result.u = u;
	    result.v = v;
	    return result;
	}
}
