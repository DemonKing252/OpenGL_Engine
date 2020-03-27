/*****************************
File: shader.vert (Fragment Shader)
Author: Liam Blake
Created: 2020-02-12
Modified: 2020-03-12
*****************************/

#version 430 core
#define MAX_LIGHTS 2

in vec3 vs_colour;
in vec2 vs_texture;
out vec4 fragColour;
in vec3 fragPos;
in vec3 vs_normal;

uniform sampler2D texture0;


struct PointLight
{
	vec3 position;
	vec3 colour;
	float strength;

};
uniform int fragStyle;
uniform float alpha;
uniform PointLight pLight[MAX_LIGHTS];
uniform vec2 uvMapping;
uniform int shouldAnimate;

uniform vec3 mCameraFacing;
uniform float fog_fallOffEnd;
uniform float fog_fallOffStart;
uniform vec4 fog_colour;

void main()
{
	
	vec3 ambient = vec3(0.3, 0.3, 0.3);	
	vec3 result = vec3(0);
	vec3 specular = vec3(0);
	vec3 diffuse = vec3(0);

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		// Do we want the distance between the light postion and camera to affect the intensity of reflected light?
		// In real life yes so I'm doing that here

		float distance = length(pLight[i].position - fragPos);


		// Calculate Diffuse
		vec3 norm = normalize(vs_normal);
		vec3 lightDir = normalize(pLight[i].position - fragPos);
		float diff = max(dot(norm, lightDir), 0.0f);
		diffuse += diff * pLight[i].colour * vec3(pLight[i].strength) / distance;
		
		// Calculate Specular
		vec3 viewDir = normalize(mCameraFacing - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32) / distance;
		specular += pLight[i].strength * spec * pLight[i].colour;
		
		// Calculate the result of the all three lighting types
		result = (ambient + specular + diffuse);	
		
	}
	
	if (shouldAnimate == 0)
	{

		if (fragStyle == 0)
			fragColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		else if (fragStyle == 1)
			fragColour = texture(texture0, vs_texture) * vec4(vs_colour, alpha);
		else if (fragStyle == 2)
			fragColour = vec4(vs_colour, alpha);
		else if (fragStyle == 3)
			fragColour = texture(texture0, vs_texture) * vec4(1,1,1, alpha);
		else if (fragStyle == 4)
			fragColour = texture(texture0, vs_texture) * vec4(1,1,1, alpha) * vec4(result, 1.0f);
		else if (fragStyle == 5)
			fragColour = vec4(vs_colour, alpha) * vec4(result, 1.0f);
		else if (fragStyle == 6)
			fragColour = vec4(result, alpha);
		else if (fragStyle == 7)
			fragColour = texture(texture0, vs_texture) * vec4(vs_colour, alpha) * vec4(result, 1.0f);
			
	}
	else
	{
		fragColour = texture(texture0, vs_texture + uvMapping) * vec4(1,1,1, alpha) * vec4(result, 1.0f);
	}

	// Linear fog

	if (fragStyle != (0 | 1 | 2 | 3))
	{
		float distance = length(fragPos - mCameraFacing);
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