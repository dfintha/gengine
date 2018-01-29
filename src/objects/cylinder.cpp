#include "objects/objects.hpp"
#include "gl.hpp"

#include <cmath>

namespace obj {
	void cylinder::create() {
		using voidptr = void *;
		constexpr int N = 32;
	    constexpr int M = 2;
	    vertices = N * M * 6;

	    glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    constexpr float D = float(1) / float(N);
	    constexpr float H = float(1) / float(M);

	    float baseAngle = 0;
	    float baseHeight = 0;

	    data = new vertex_data[vertices];

	    for (int p = 0; p < M; ++p) {
	        const int offset = p * N * 6;

	        for (int i = offset; i < offset + N * 6; i += 6) {
	            data[i + 0].position = 
	            	geo::vector(std::cos((baseAngle + D) * 2 * M_PI),
	                            baseHeight + H,
	                            std::sin((baseAngle + D) * 2 * M_PI));
	            data[i + 0].normal = 
	            	geo::normalize(data[i + 0].position * geo::vector(1, 0, 1));
	            data[i + 0].u = 1;
	            data[i + 0].v = baseAngle;

	            data[i + 1].position = 
	            	geo::vector(std::cos((baseAngle + D) * 2 * M_PI),
	                            baseHeight,
	                            std::sin((baseAngle + D) * 2 * M_PI));
	            data[i + 1].normal = 
	            	geo::normalize(data[i + 1].position * geo::vector(1, 0, 1));
	            data[i + 1].u = 0;
	            data[i + 1].v = baseAngle;

	            data[i + 2].position = 
	            	geo::vector(std::cos(baseAngle * 2 * M_PI),
	                            baseHeight,
	                            std::sin(baseAngle * 2 * M_PI));
	            data[i + 2].normal = 
	            	geo::normalize(data[i + 2].position * geo::vector(1, 0, 1));
	            data[i + 2].u = 0;
	            data[i + 2].v = baseAngle;

	            data[i + 3].position = 
	            	geo::vector(std::cos(baseAngle * 2 * M_PI),
	                            baseHeight,
	                            std::sin(baseAngle * 2 * M_PI));
	            data[i + 3].normal = 
	            	geo::normalize(data[i + 3].position * geo::vector(1, 0, 1));
	            data[i + 3].u = 0;
	            data[i + 3].v = baseAngle;

	            data[i + 4].position = 
	            	geo::vector(std::cos(baseAngle * 2 * M_PI),
	                            baseHeight + H,
	                            std::sin(baseAngle * 2 * M_PI));
	            data[i + 4].normal = 
	            	geo::normalize(data[i + 4].position * geo::vector(1, 0, 1));
	            data[i + 4].u = 1;
	            data[i + 4].v = baseAngle;

	            data[i + 5].position = 
	            	geo::vector(std::cos((baseAngle + D) * 2 * M_PI),
	                            baseHeight + H,
	                            std::sin((baseAngle + D) * 2 * M_PI));
	            data[i + 5].normal = 
	            	geo::normalize(data[i + 5].position * geo::vector(1, 0, 1));
	            data[i + 5].u = 1;
	            data[i + 5].v = baseAngle;

	            baseAngle += D;
	        }

	        baseHeight += H;
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
}
