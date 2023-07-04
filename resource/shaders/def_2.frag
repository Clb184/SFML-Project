#version 330 core

out vec4 FragColor;

//Color
in vec4 color;

in float time;
in float isBlur;

//Texture coordinates
in vec2 texCoord;
in vec2 texCoord2;
//in vec2 center;

//Binded texture
uniform sampler2D tex0;

//Constants for different functions...
const int BLACK_SPRITE = 0x1;


void main() {
	if(isBlur != 0.0){
	//if(false){
	float detail = 3.0;
	float matsides = int((cos(time * 3) * (detail) + (detail)) * 0.5);
	float sizeofside = 1.0 + 2.0 * matsides;
	float powofside = pow(sizeofside, 2.0);
	float texOffsetX = 1.0 / texCoord2.x;
	float texOffsetY = 1.0 / texCoord2.y;
	float steps = 1.0;
	float resj, resi;
	vec3 col = vec3(0.0);
	for(float i = -matsides; i <= matsides; i += steps ){
			resi = max(min(matsides, i + steps), 0.0);
		for(float j = -matsides; j <= matsides; j += steps ) {
			resj = max(min(matsides, j + steps), -matsides);
			col += texture(tex0, texCoord + vec2(texOffsetX * resj, texOffsetY * resi)).rgb;
		}
	}
	col /= powofside * (1.0 / steps);
	vec4 getTexel = texture(tex0, texCoord);
	float r = getTexel.r;
	float g = getTexel.g;
	float b = getTexel.b;
	float a = getTexel.a;
	FragColor = vec4(col, a) * color;
	}
	else {
		FragColor = texture(tex0, texCoord) * color;
	}
	//getTexel = FragColor;
	// r = getTexel.r;
	// g = getTexel.g;
	// b = getTexel.b;
	// a = getTexel.a;
	//float adding = abs(sin(time));
	//float lestcol = min(min(r, g), b);

	//FragColor = vec4(adding + r -lestcol, adding + g - lestcol, adding + b - lestcol, getTexel.a);
	//FragColor = texture(tex0, texCoord) * color;
	//FragColor = vec4(1.0f) * color;
	//if(texCoord.x >= center.x - 0.1 && texCoord.x <= center.x + 0.1 &&
	//texCoord.y >= center.y - 0.1 && texCoord.y <= center.y + 0.1)
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
