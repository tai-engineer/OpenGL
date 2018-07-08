#version 400

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shiniess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 fragPos;
in vec2 texCoord;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform Light light;
uniform Material material;

out vec4 color;

void main(){
	// ambient
	vec3 ambient =  light.ambient * vec3(texture(material.diffuse, texCoord));

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = vec3(texture(material.diffuse, texCoord)) * diff * light.diffuse;

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = vec3(texture(material.specular, texCoord)) * spec * light.specular;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
}
