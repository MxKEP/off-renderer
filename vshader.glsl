#version 150

in vec3 vPos;
in vec3 vColor;
out vec3 color;

uniform mat4 modelview;
uniform mat4 projection;

void main() {
	gl_Position = projection * modelview * vec4(vPos, 1.0);
	color = vColor;
}
