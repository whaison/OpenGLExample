#version 150

uniform mat4 u_modelViewProjectionMatrix;
uniform mat3 u_normalMatrix;

in vec4 a_vertex;
in vec3 a_normal;
in vec2 a_texCoord;

out vec2 v_texCoord;
out vec3 v_normal;

void main(void)
{
    v_texCoord = a_texCoord;

    v_normal = u_normalMatrix * a_normal;;

	gl_Position = u_modelViewProjectionMatrix * a_vertex;
}
