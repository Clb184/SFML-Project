#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

struct light{
	vec3 pos;
	vec4 color;
};

uniform int lightCnt;


// Inputs the color from the Vertex Shader
in vec4 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 normVec;
in vec3 curPos;
uniform vec3 camPos;
uniform vec3 lightPos;
uniform light lightVec[16];

//uniform vec2 wh;
// Gets the Texture Unit from the main function
uniform sampler2D tex0;
//uniform sampler2D tex2;

in float visib;

void main()
{
	vec3 norm = normalize(normVec);
	//norm = texture(tex2, texCoord.xy).rgb;
	//norm = normalize(texture(tex2, texCoord.xy).rgb * 2.0 - 1.0);
	//norm = norm * 0.5 + 0.5;
	
	
	vec3 hold = camPos;
	vec4 resultLight = vec4(1.0);
	for(int i = 0; i < lightCnt; i++){
		vec3 ldir = normalize(lightVec[i].pos - curPos);
		float diffuse = max(dot(norm, ldir), 0.0f);
		resultLight *= diffuse * lightVec[i].color;
	}

	//float alpha = dot(texture(tex0, texCoord.xy), texture(tex0, texCoord.xy));
	vec4 col = (resultLight + vec4(0.2)) * texture(tex0, texCoord) * color;
	col.a = texture(tex0, texCoord.xy).a;
	if(col.a == 0.0)
		discard;
	else
		FragColor = col;
		//FragColor = texture(tex0, texCoord);
	//FragColor = vec4(1.0);
	//FragColor = 1.0 * (diffuse + vec4(0.2, 0.2, 0.2, 0.0));
	//FragColor.a = 1.0;
	//FragColor = mix(vec4(0.5, 0.5, 0.0, 1.0), FragColor, visib);
}