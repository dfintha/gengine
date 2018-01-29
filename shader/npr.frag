#version 330
precision highp float;

uniform sampler2D sampler;
uniform vec3 kd, ka;
uniform vec3 La;
uniform int textured;

in vec3 wNormal;
in vec3 wView;
in vec3 wLight;
in vec2 uvCoord;

out vec4 fragmentColor;

void main() {
    vec3 N = normalize(wNormal);
    vec3 V = normalize(wView);
    vec3 L = normalize(wLight);

    vec3 result;
    if (textured == 1) {
        result = texture(sampler, uvCoord).xyz;
    } else {
        result = kd;
    }

    float y = (dot(N, L) > 0.5) ? 1 : 0.5;

    if (abs(dot(N, V)) < 0.2) {
        fragmentColor = vec4(ka * La, 1);
    } else {
        fragmentColor = vec4(ka * La + y * result, 1);
    }
}
