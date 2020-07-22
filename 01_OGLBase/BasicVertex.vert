#version 330 core

in vec3 inVertexPosition;
//in float inTextureCoordX;
in vec2 inTextureCoordXY;
in int inNorm;

out vec3 outVertPos;
out vec3 outNorm;
out vec2 outTexCoord;
out float outOpaque;

uniform mat4 MVP;
uniform mat4 world;
uniform mat4 worldIT;

void main()
{
	gl_Position = MVP * vec4( inVertexPosition, 1 );
	outVertPos = (world * vec4(inVertexPosition, 1)).xyz;
	outTexCoord = vec2(inTextureCoordXY.x / 256.f , 1.f - (inTextureCoordXY.y / 256.f));
	outOpaque = 1.f;

	if (inNorm < 1) {
		outNorm = vec3(0, 1, 0);
	} else if (inNorm < 2) {
		outNorm = vec3(0, -1, 0);
	} else if (inNorm < 3) {
		outNorm = vec3(-1, 0, 0);
	} else if (inNorm < 4) {
		outNorm = vec3(1, 0, 0);
	} else if (inNorm < 5) {
		outNorm = vec3(0, 0, 1);
	} else if (inNorm < 6) {
		outNorm = vec3(0, 0, -1);
	} else {
		outNorm = vec3(0, 1, 0);
		outOpaque = 0.8f;
	}

	outNorm = (worldIT * vec4(outNorm, 1)).xyz;
}