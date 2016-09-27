#version 150

uniform sampler2D u_texture; 

in float v_intensity;
in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_lightDirection;
in vec3 v_view;
in vec3 v_vertex;

out vec4 fragColor;

void main(void)
{
    vec3 ldir = normalize(v_lightDirection);
    vec3 vdir = normalize(v_view);
    vec3 halfV = normalize(ldir + vdir);
    float spec = max(dot(halfV, v_normal), 0);
    spec = pow(spec, 50);
	fragColor = texture(u_texture, v_texCoord) * v_intensity + vec4(v_vertex.x, v_vertex.y, v_vertex.z, 1.0f) * spec;
}
