#version 400 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

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
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
Light light;

void main()
{
    material.ambient = vec3(texture(ourTexture1, TexCoords));
	material.diffuse = vec3(texture(ourTexture1, TexCoords));
	material.specular = vec3(texture(ourTexture2, TexCoords));
	material.shininess = 128;
	 
	light.position = lightPos;
	light.ambient = vec3(1.0f, 0.5f, 0.31f);
	light.diffuse = vec3(0.6, 0.6, 0.6);
	light.specular = vec3(1.0, 1.0, 1.0);


	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuse = max(dot(norm,lightDir),0.0f);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess );
	
    FragColor = vec4(( light.ambient * material.ambient + diffuse * light.diffuse * material.diffuse + specular * light.specular * material.specular ) * lightColor, 1.0);
}