#version 150

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform vec4 u_plane;

in vec4 a_vertex;
in vec3 a_normal;

out vec3 v_normal;
out vec3 v_eye;
out float v_distance;

void main()
{
	vec4 vertex = u_modelMatrix * a_vertex;

    v_distance = dot(u_plane, vertex);
	// gl_ClipDistance[0] = v_distance;

	vertex = u_viewMatrix * vertex;

	v_eye = -vec3(vertex);

	v_normal = u_normalMatrix * a_normal;
		
	gl_Position = u_projectionMatrix * vertex;
}    