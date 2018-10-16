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
    vec3  direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
    vec3 lightDir = normalize(light.position - FragPos);
        //vec3 lightDir = normalize(light.position - FragPos);
        //float diff = dot(norm, lightDir)*0.5+0.5;
    float diff = max(0,dot(norm, lightDir));
    vec3 diffuse =  (diff * vec3(texture(material.diffusetexture, TexCoords)) ) * light.diffuse ;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.speculartexture, TexCoords))) ;
            
    // spot light 
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    
    diffuse *= intensity;
    specular *= intensity;


    // atten 
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
    light.quadratic * (distance * distance));

    vec3 result = (ambient + diffuse + specular)*attenuation;
    FragColor = vec4(result, 1.0);

}