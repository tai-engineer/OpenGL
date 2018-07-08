#version 400

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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


uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Light light;
uniform Material material;

out vec4 color;

void main(){
	// ambient
	vec3 ambient = material. ambient + light.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = material.diffuse *diff * light.diffuse;

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = material.specular * spec * light.specular;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
}
