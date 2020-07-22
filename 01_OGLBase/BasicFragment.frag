#version 330 core


in vec3 outVertPos;
in vec3 outNorm;
in vec2 outTexCoord;
in float outOpaque;

out vec4 outColour;


uniform vec3 lightSource = vec3(1, 2, 5);

uniform sampler2D texSampler;

void main()
{
	vec3 norm = normalize(outNorm);
	vec3 lightDir = normalize(-lightSource);
	float diff = max(dot(norm, -lightDir), 0.8);
	outColour =  diff * texture(texSampler, outTexCoord);
}