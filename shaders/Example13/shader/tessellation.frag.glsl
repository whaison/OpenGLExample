#version 410 core

layout(location = 0, index = 0) out vec4 fragColor;

in vec4 v_position;

void main(void)
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // fragColor = v_position;
}
