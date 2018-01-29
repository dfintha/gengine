#version 330
precision highp float;

uniform mat4 M, MI, MVP;
uniform vec4 light;
uniform vec3 camera;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

out vec3 wNormal;
out vec3 wView;
out vec3 wLight;
out vec2 uvCoord;

void main() {
    gl_Position = vec4(position, 1) * MVP;
    vec4 world = vec4(position, 1) * M;

    wNormal = (MI * vec4(normal, 0)).xyz;
    wView = camera * world.w - world.xyz;
    wLight = light.xyz * world.w - world.xyz * light.w;
    uvCoord = texture;
}
