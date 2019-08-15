#version 400 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform vec4 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 front;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

struct Material{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
Material material;

struct Light {
	vec4 lightDir;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
Light light;

struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
SpotLight spotLight;

vec3 CalcPointLight(Light light)
{
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	vec3 norm = normalize(Normal);
	vec3 lightDir;
	float distance;

	if(light.lightDir.w == 0.0) // direction
	{
		lightDir = normalize(vec3(light.lightDir));
	}
	else if(light.lightDir.w == 1.0)  // position
	{
	//  À•ºıº∆À„
	    distance = length( vec3(light.lightDir) - FragPos);
		lightDir = normalize(vec3(light.lightDir) - FragPos); 
	}
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	float diffuse = max(dot(norm,lightDir),0.0f);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	
    result = vec3(( light.ambient * material.ambient + diffuse * light.diffuse * material.diffuse + specular * light.specular * material.specular ) * lightColor * (attenuation));

	return result;
}

vec3 CalcSpotLight(SpotLight spotLight)
{
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	float thera = dot(normalize(vec3(spotLight.position) - FragPos),-spotLight.direction);
	float spotI = 0.0f;
	float epsilon = cos(radians(spotLight.cutoff)) - cos(radians(spotLight.outerCutOff));
	spotI = clamp( (thera - cos(radians(spotLight.outerCutOff))) / epsilon ,0.0,1.0);

	vec3 norm = normalize(Normal);
	vec3 lightDir;
	float distance;

	lightDir = -spotLight.direction;
	//  À•ºıº∆À„
	distance = length( vec3(spotLight.position) - FragPos);
	float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * distance * distance);

	float diffuse = max(dot(norm,lightDir),0.0f);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	
    result = vec3(( spotLight.ambient * material.ambient + diffuse * spotLight.diffuse * material.diffuse + specular * spotLight.specular * material.specular ) * lightColor * (attenuation * spotI));

	return result;
}

void main()
{
    material.ambient = vec3(texture(ourTexture1, TexCoords));
	material.diffuse = vec3(texture(ourTexture1, TexCoords));
	material.specular = vec3(texture(ourTexture2, TexCoords));
	material.shininess = 64;

	spotLight.position = viewPos;
	spotLight.direction = front;
	spotLight.outerCutOff = 17.5f;
	spotLight.cutoff = 12.5f;
    spotLight.constant = 1.0;
	spotLight.linear = 0.09;
	spotLight.quadratic = 0.032;
	spotLight.ambient = vec3(0.0f, 0.0f, 0.0f);
	spotLight.diffuse = vec3(1.0, 1.0, 1.0);
	spotLight.specular = vec3(1.0, 1.0, 1.0);

	light.constant = 1.0;
	light.linear = 0.09;
	light.quadratic = 0.032;

	light.lightDir = lightPos;
	light.ambient = vec3(1.0f, 0.5f, 0.31f);
	light.diffuse = vec3(0.6, 0.6, 0.6);
	light.specular = vec3(1.0, 1.0, 1.0);

	vec3 result = vec3(0.0f,0.0f, 0.0f);
	result += CalcPointLight(light);
	result += CalcSpotLight(spotLight);
	FragColor = vec4(result,1.0f);
	
}