#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    sampler2D diffusetexture;
    vec3 diffuse;
    sampler2D speculartexture;
    vec3 specular;
    float shininess;
}; 
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

void main()
{
    // ambient
    float ambientStrength = 1.0;
	float specularStrength = 1.0;
    vec3 ambient = light.ambient * vec3(texture(material.diffusetexture, TexCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    //float diff = dot(norm, lightDir)*0.5+0.5;
    float diff = max(0,dot(norm, lightDir));
    vec3 diffuse =  (diff * vec3(texture(material.diffusetexture, TexCoords)) ) * light.diffuse ;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.speculartexture, TexCoords))) ;
	

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}