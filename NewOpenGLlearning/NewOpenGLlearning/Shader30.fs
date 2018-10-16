#version 330 core

in vec2 TexCoords;
out vec4 FragColor;
float near = 0.1; 
float far  = 20.0; 
uniform sampler2D texture_diffuse1;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{    
	
	// 1. orgin :
	//FragColor = texture(texture_diffuse1, TexCoords);
	

	// 2. DEPTH :
	//	FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

	// 3. linear :
	float depth = LinearizeDepth(gl_FragCoord.z) / far; 		// 为了演示除以 far
    FragColor = vec4(vec3(depth), 1.0);

}