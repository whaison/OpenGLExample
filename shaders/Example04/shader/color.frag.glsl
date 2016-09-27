#version 150

uniform sampler2D u_texture; 

in vec2 v_texCoord;
in vec3 v_normal;

out vec4 fragColor;

void main(void)
{
    vec3 v_lightDirection = vec3(1.0f, 1.0f, 1.0f);
    v_lightDirection = normalize(v_lightDirection);
    vec4 color = texture(u_texture, v_texCoord);
    float NDotL = dot(v_lightDirection, v_normal);
    NDotL = max(NDotL, 0.0f);
	fragColor = color * NDotL + 0.2 * color;
}
