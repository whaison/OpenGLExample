#version 150

uniform sampler2D u_texture; 

in vec2 v_texCoord;

out vec4 fragColor;

float rand(float x) {
    x = int(x * 9301 + 49297) % 233280;
    return x / 233280.0;
}

void main(void)
{
	vec4 color = texture(u_texture, v_texCoord);
	float grey = color.r*0.299 + color.g*0.587 + color.b*0.114;

	if (v_texCoord.x >= color.x)
	{
		fragColor = vec4(grey, grey, grey, 1.0f);
	}
	else if (v_texCoord.y <= color.y) {
		fragColor = vec4(color.x, grey, color.y, 1.0f);
	}
	else
	{
		fragColor = color;
	}
}
