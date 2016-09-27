#version 150

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform vec3 u_lightDirection;

in vec4 a_vertex;
in vec3 a_normal;
in vec2 a_texCoord;

out float v_intensity;
out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_lightDirection;
out vec3 v_view;
out vec3 v_vertex;

void main(void)
{
	// Now the normal is in world space, as we pass the light in world space.
	vec3 normal = u_normalMatrix * a_normal;

    // Intensity is lambert without emissive color. al is the ambient, hard coded light factor.
 	v_intensity = 0.3 + max(dot(normal, u_lightDirection), 0.0);

	v_texCoord = a_texCoord;

    vec4 view = u_modelMatrix * a_vertex;

    v_vertex = vec3(view);
    // cameraPos=vec3(0, 0, 0)
    v_view = vec3(0, 0, 5) - vec3(view);

    v_normal = normal;
    v_lightDirection = u_lightDirection;

	gl_Position = u_viewProjectionMatrix * u_modelMatrix * a_vertex;
}
