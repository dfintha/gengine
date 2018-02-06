#include "objects/objects.hpp"
#include "gl.hpp"

#include <cmath>
#include <fstream>
#include <sstream>

namespace obj {
	obj_model::obj_model(const char *path) :
		file(path)
    { }

	void obj_model::create() {
		using voidptr = void *;

		glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    std::vector<geo::vector> vertex_array;
	    std::vector<geo::vector> normal_array;
	    std::vector<vertex_data> face_array;

	    std::ifstream stream;
	    stream.open(file);
	    if (stream.fail())
        	return;

        const auto read_vector = [&] (const std::string& line) {
	        std::stringstream str(line);
	        std::string kind;
	        float x, y, z;
	        str >> kind;
	        str >> x >> y >> z;
	        return geo::vector(x, y, z);
	    };

	    const auto read_face = [&] (std::string line) {
	        for (char& c : line) {
	            if (c == '/' || c == 'f')
	                c = ' ';
	        }

	        std::stringstream str(line);

	        for (int i = 0; i < 3; ++i) {
	            int v, n;
	            vertex_data result;
	            str >> v;
	            str >> n;
	            result.position = vertex_array[v - 1];
	            result.normal = normal_array[n - 1];

	            switch (i) {
	                case 0:
	                    result.u = 1;
	                    result.v = 0;
	                    break;
	                case 1:
	                    result.u = 1;
	                    result.v = 1;
	                    break;
	                case 2:
	                    result.u = 0;
	                    result.v = 1;
	                    break;
	            }

	            face_array.push_back(result);
	        }
	    };

	    std::string line;
	    while (std::getline(stream, line)) {
	        if (line[0] == 'v') {
	            if (line[1] == 'n') {
	                normal_array.push_back(read_vector(line));
	            } else {
	                vertex_array.push_back(read_vector(line));
	            }
	        } else if (line[0] == 'f') {
	            read_face(line);
	        }
	    }

	    stream.close();
	    vertex_array.clear();
	    normal_array.clear();

	    vertices = face_array.size();
	    data = new vertex_data[vertices];

	    for (size_t i = 0; i < face_array.size(); ++i)
	        data[i] = face_array[i];

	    face_array.clear();

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
