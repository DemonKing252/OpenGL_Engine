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
uniform PointLight pLight[MAX_LIGHTS];

uniform vec3 mCameraFacing;

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

		float distance = length(pLight[i].position - mCameraFacing);


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
	if (fragStyle == 0)
		fragColour = vec4(0);
	else if (fragStyle == 1)
		fragColour = texture(texture0, vs_texture) * vec4(vs_colour, 1.0f);
	else if (fragStyle == 2)
		fragColour =  vec4(vs_colour, 1.0f);
	else if (fragStyle == 3)
		fragColour = texture(texture0, vs_texture);
	else if (fragStyle == 4)
		fragColour = texture(texture0, vs_texture) * vec4(result, 1.0f);
	else if (fragStyle == 5)
		fragColour = vec4(vs_colour, 1.0f) * vec4(result, 1.0f);
	else if (fragStyle == 6)
		fragColour = vec4(result, 1.0f);
	else if (fragStyle == 7)
		fragColour = texture(texture0, vs_texture) * vec4(vs_colour, 1.0f) * vec4(result, 1.0f);

	
}