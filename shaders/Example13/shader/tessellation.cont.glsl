#version 410 core

// Working with quads, so four vertices out
layout(vertices = 4) out;

void main(void)
{
	// Outer tessellation level, so we have four "outer" rows and columns
	gl_TessLevelOuter[0] = 24.0;
	gl_TessLevelOuter[1] = 24.0;
	gl_TessLevelOuter[2] = 24.0;
	gl_TessLevelOuter[3] = 24.0;

	// Inner tessellation level, so we have four "inner" rows and columns
	gl_TessLevelInner[0] = 24.0;
	gl_TessLevelInner[1] = 24.0;

	// Finally, we have a four by four tessellated plane
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
