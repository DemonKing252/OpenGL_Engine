/*****************************
File: FragmentCore.hlsl (Fragment Shader)
Author: Liam Blake
Created: 2020-02-12
Modified: 2020-04-13
*****************************/
#version 430 core
#define MAX_LIGHTS 2

in vec3 vs_unadjustedfragPos;
in vec3 vs_color;
in vec2 vs_texture;
out vec4 fragColour;
in vec3 vs_fragPos;
in vec3 vs_normal;

uniform sampler2D texture0;


struct PointLight
{
	vec3 position;
	vec3 colour;
	float strength;

};


uniform int changeHeight;
uniform int fragStyle;

uniform float alpha;
uniform float fog_fallOffEnd;
uniform float fog_fallOffStart;

uniform vec2 uvMapping;
uniform vec3 mCameraFacing;
uniform vec3 ambient;
uniform vec4 fog_colour;
uniform vec4 diffAlbedo;

uniform PointLight pLight[MAX_LIGHTS];

void main()
{
	vec3 result = vec3(0);
	vec3 specular = vec3(0);
	vec3 diffuse = vec3(0);

	const float fallOffStart = 1.0f;
	const float fallOffEnd = 5.0f;

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		// Do we want the distance between the light postion and camera to affect the intensity of reflected light?
		// In real life yes so I'm doing that here

		float distance = length(pLight[i].position - vs_fragPos);

		if (distance <= fallOffEnd)
		{
			// Calculate Diffuse
			vec3 norm = normalize(vs_normal);
			vec3 lightDir = normalize(pLight[i].position - vs_fragPos);
			float diff = max(dot(norm, lightDir), 0.0f);
			diffuse += diff * pLight[i].colour * pLight[i].strength * ((fallOffEnd - distance) / (fallOffEnd - fallOffStart));
			
			// Calculate Specular
			vec3 viewDir = normalize(mCameraFacing - vs_fragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32) / (distance * distance);
			specular += pLight[i].strength * spec * pLight[i].colour;
		}
	}
	// Calculate the result of the all three lighting types
	result = (ambient + diffuse + specular);	
	// I cannot use enumerators in the core shaders >:(
	
	if (fragStyle == 0)
		fragColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	else if (fragStyle == 1)
		fragColour = texture(texture0, vs_texture + uvMapping) * vec4(vs_color, alpha);
	else if (fragStyle == 2)
		fragColour = vec4(vs_color, alpha);
	else if (fragStyle == 3)
		fragColour = texture(texture0, vs_texture + uvMapping) * vec4(1,1,1, alpha);
	else if (fragStyle == 4)
		fragColour = texture(texture0, vs_texture + uvMapping) * vec4(1,1,1, alpha) * vec4(result, 1.0f);
	else if (fragStyle == 5)
		fragColour = vec4(vs_color, alpha) * vec4(result, 1.0f);
	else if (fragStyle == 6)
		fragColour = vec4(result, alpha);
	else if (fragStyle == 7)
		fragColour = texture(texture0, vs_texture + uvMapping) * diffAlbedo;
	else if (fragStyle == 8)
		fragColour = texture(texture0, vs_texture + uvMapping) * vec4(vs_color, alpha) * vec4(result, 1.0f);

	// Future project: Change wave fragment color according to their height.
	/*
	// 0.0f -> 3.0f
	if (changeHeight == 1)
	{
		if (vs_unadjustedfragPos.y > 0.0f)
			fragColour = vec4(fragColour.x, fragColour.y, fragColour.z + 1.0f, alpha);
		else
			fragColour = vec4(fragColour.x, fragColour.y, fragColour.z, alpha);

	}
	*/

	// Linear fog
	
	if (fragStyle != (0 | 1 | 2 | 3))
	{
		float distance = length(vs_fragPos - mCameraFacing);
		float fog_factor = (fog_fallOffEnd - distance) /
		                  (fog_fallOffEnd - fog_fallOffStart);
	
		fog_factor = clamp(fog_factor, 0.0, 1.0);
	
		/*********************************************************
		// Interpolate each property of the fragment
		// IE: Lighting, Colour, Texture Sampler, and Fog
		*********************************************************/
	
		fragColour = mix(fog_colour, fragColour, fog_factor);
	}

}