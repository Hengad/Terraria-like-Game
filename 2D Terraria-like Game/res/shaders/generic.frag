#version 330 core

in vec2 TexCoord;
in vec3 Color;
in vec2 Pos;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D texSampler;

uniform int numOfLights;
uniform vec2 lightPositions[100];

vec3 calcLight(vec2 lightPos, vec2 fragPos, float maxDistance);
vec3 calcLightSigmoid(vec2 lightPos, vec2 fragPos, float maxDistance);

void main()
{
	float ambientStrength = 1.0;
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i <= numOfLights; i++)
	{
		result += (calcLightSigmoid(Pos, lightPositions[i], 3400.0));

		if(result.r > 1.0)
		{
			result.r = 1.0;
		}
		if(result.g > 0.88)
		{
			result.g = 0.88;
		}
		if(result.b > 0.4)
		{
			result.b = 0.4;
		}
	}

	FragColor = texture(texSampler, TexCoord) * (vec4(result, 1.0) + vec4(ambient, 1.0));
}

vec3 calcLight(vec2 lightPos, vec2 fragPos, float maxDistance)
{
	float dist = distance(fragPos, lightPos);
	float attenuation = clamp(0.5 - dist / maxDistance, 0.0, 0.5);
	attenuation *= attenuation;
	attenuation *= attenuation;
	attenuation *= attenuation;

	return vec3(1.0, 0.88, 0.4) * attenuation * 200;
}

vec3 calcLightSigmoid(vec2 lightPos, vec2 fragPos, float maxDistance)
{
	float dist = distance(fragPos, lightPos);
	float attenuation = (-2 / (1 + pow(2.718, -0.5*(dist/100)))) + 2;

	return vec3(1.0, 0.88, 0.4) * attenuation;
}