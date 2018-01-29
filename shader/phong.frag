#version 330
precision highp float;

uniform sampler2D sampler;
uniform vec3 kd, ks, ka;
uniform vec3 La, Le;
uniform float shine;
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
    vec3 H = normalize(L + V);

    vec3 result;
    if (textured == 1) {
        result = texture(sampler, uvCoord).xyz;
    } else {
        result = kd;
    }

    float cost = max(dot(N, L), 0);
    float cosd = max(dot(N, H), 0);

    vec3 color = ka * La + (result * cost + ks * pow(cosd, shine)) * Le;
    fragmentColor = vec4(color, 1);
}
