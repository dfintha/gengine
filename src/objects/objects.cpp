#include "objects/objects.hpp"
#include "gl.hpp"

namespace obj {
	void object_base::draw(const eng::scene& scene) const {
		auto m = geo::scaling(scale.x, scale.y, scale.z) *
	           	 geo::rotation(angle, rotation.x, rotation.y, rotation.z) *
	           	 geo::translation(position.x, position.y, position.z);

	    auto mi = geo::translation(-position.x, -position.y, -position.z) *
	           	  geo::rotation(-angle, rotation.x, rotation.y, rotation.z) *
	           	  geo::scaling(1 / scale.x, 1 / scale.y, 1 / scale.z);

	    auto mvp = m * scene.cam.view() * scene.cam.projection();

	    int location;

	    location = glGetUniformLocation(scene.program, "M");
    	glUniformMatrix4fv(location, 1, GL_TRUE, m.as_uniform());

    	location = glGetUniformLocation(scene.program, "MI");
    	glUniformMatrix4fv(location, 1, GL_TRUE, mi.as_uniform());

    	location = glGetUniformLocation(scene.program, "MVP");
    	glUniformMatrix4fv(location, 1, GL_TRUE, mvp.as_uniform());

	    glFrontFace(draw_side == inside ? GL_CW : GL_CCW);

	    switch (draw_mode) {
	    	case polywire:
	    		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	    		break;
	    	case polyfill:
	    		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	    		break;
	    }

	    if (textured) {
	        location = glGetUniformLocation(scene.program, "sampler");
	        glUniform1i(location, GL_TEXTURE0);
	        glActiveTexture(GL_TEXTURE0);
	        glBindTexture(GL_TEXTURE_2D, texture->id);
	    }
	    
	    location = glGetUniformLocation(scene.program, "textured");
	    glUniform1i(location, textured ? 1 : 0);

	    location = glGetUniformLocation(scene.program, "light");
	    glUniform4fv(location, 1, scene.light_position);

	    location = glGetUniformLocation(scene.program, "Le");
	    glUniform3fv(location, 1, scene.light_color);

	    location = glGetUniformLocation(scene.program, "La");
	    glUniform3fv(location, 1, scene.ambient_color);

	    location = glGetUniformLocation(scene.program, "camera");
	    glUniform3fv(location, 1, scene.cam.position);

	    location = glGetUniformLocation(scene.program, "kd");
	    glUniform3fv(location, 1, diffuse);

	    location = glGetUniformLocation(scene.program, "ks");
	    glUniform3fv(location, 1, specular);

	    location = glGetUniformLocation(scene.program, "ka");
	    glUniform3fv(location, 1, ambient);

	    location = glGetUniformLocation(scene.program, "shine");
	    glUniform1f(location, shine);

	    glBindVertexArray(vao);
	    glDrawArrays(GL_TRIANGLES, 0, vertices);
	    glBindVertexArray(0);
	}

	vertex_data object_base::vertex_at(float, float) const {
		return vertex_data();
	}
}
