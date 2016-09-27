#version 150

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;
uniform mat3 u_normalMatrix;

in vec4 a_vertex;
in vec3 a_normal;

out vec3 v_normal;
out vec3 v_eye;

void main()
{
	vec4 vertex = u_modelViewMatrix * a_vertex;

    vec3 cameraPos = vec3(0, 0, 5);

	v_eye = cameraPos - vec3(vertex);

	v_normal = u_normalMatrix * a_normal;
		
	gl_Position = u_projectionMatrix * vertex;
}    