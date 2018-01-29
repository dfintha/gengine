#include "objects/objects.hpp"
#include "gl.hpp"

#include <cmath>

namespace obj {
	void rectangle::create() {
		using voidptr = void *;
		vertices = 6;

	    glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    data = new vertex_data[vertices];

	    data[0].position = geo::vector(-0.5, 0, -0.5);
	    data[1].position = geo::vector(-0.5, 0,  0.5);
	    data[2].position = geo::vector( 0.5, 0, -0.5);
	    data[3].position = geo::vector(-0.5, 0,  0.5);
	    data[4].position = geo::vector( 0.5, 0,  0.5);
	    data[5].position = geo::vector( 0.5, 0, -0.5);

	    const geo::vector normal = geo::normalize(geo::cross(data[0].position -
                            				       			 data[1].position,
                            				       			 data[2].position -
                            				       		 	 data[1].position)) 
	    							* -1;

	    for (size_t i = 0; i < vertices; ++i) {
	        data[i].normal = normal;
	        data[i].u = std::floor(data[i].position.x) + 1;
	        data[i].v = std::floor(data[i].position.z) + 1;
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
