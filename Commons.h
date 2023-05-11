#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "Animation.h"
#define WIN32_LEAN_AND_MEAN
//#include <stack>

#define safeDelete(x) if(x){delete x; x = NULL;}

#define PI 3.1415926535897932384626433832795f
#define RAD(x) (x * (PI / 180))

inline void drawCircle(float x, float y, float rad, sf::Color c, sf::RenderWindow* target) {
	sf::CircleShape circle(rad);
	circle.setOutlineColor(c);
	circle.setOutlineThickness(1);
	circle.setFillColor(sf::Color(0));
	circle.setOrigin(rad, rad);
	circle.setPosition(sf::Vector2f(x, y));
	target->draw(circle);
}

//inline void drawCircle(float x, float y, float rad, sf::Color c, Graphics* gfx) {
//	double angle = 0.0f, 
//		i = (2 * PI * rad),
//		del = PI / i;
//	int cnt = 0;
//	for (; angle <= PI * 2; ) {
//		gfx->PutPixel(x + (cos(angle) * rad), y + (sin(angle) * rad), c);
//		angle += del;
//		cnt++;
//	}
//}

//inline void drawLine(float x, float y, float length, float dir, float off, Color c, Graphics* gfx) {
//	int cnt = 0;
//	for (int i = 0; i < length; i++ ) {
//		gfx->PutPixel(x + (cos(dir) * (i + off)), y + (sin(dir) * (i + off)), c);
//		cnt++;
//	}
//}

inline void drawLine(float x, float y, float length, float dir, float offset, sf::Color c, sf::RenderWindow* target) {
	sf::VertexArray line(sf::Lines, 2);
	line[0].color = c;
	line[1].color = c;
	line[0].position = sf::Vector2f(x + (cos(dir) * offset), y + (sin(dir) * offset));
	line[1].position = sf::Vector2f(x + (cos(dir) * offset) + (cos(dir) * length), y + (sin(dir) * offset) + (sin(dir) * length));
	target->draw(line);
}

inline void drawRect(Rect quad,sf::Transform trans, sf::Color c, sf::RenderWindow* target) {
	sf::Vertex rect[5];
	rect[0].position = { 0, 0 };
	rect[1].position = { quad.w, 0 };
	rect[2].position = { quad.w, quad.h };
	rect[3].position = { 0, quad.h };
	rect[4].position = rect[0].position;

	rect[0].color = c;
	rect[1].color = c;
	rect[2].color = c;
	rect[3].color = c;
	rect[4].color = c;

	target->draw(rect, 5, sf::LineStrip, trans);
}

#define ThisForEach(it, x) for (std::list<Enemy>::iterator it = x.begin(); it != x.end(); ++it)

/*
-x-y       ---->


*/

//inline void drawRect(float x, float y, float w, float h,  float dir, float ox, float oy,  Color c, Graphics* gfx) {
//	int cnt = 0;
//	float tx = ((-w / 2) + ox);
//	float ty = ((-h / 2) + oy);
//
//	for (int i = 0; i < w; i++) {
//			drawLine(x + (cos(dir) * (tx + i)), y + (sin(dir) * (tx + i)), h, dir + RAD(90), ty, c, gfx);
//			cnt++;
//	}
//}

inline bool  hitCheck(float x, float y, float rad) {
	float dist = hypot(x, y);
	return dist <= rad;
}

inline bool  clipCheck(float l, float r, float u, float d, float x, float y, float rad) {
	return ((x + rad < l ||
		x - rad > r) ||
		(y + rad < u ||
		y - rad > d));
}

inline void normRad(float& ang) {
	if (ang > RAD(360)) {
		while (ang > RAD(360)) {
			ang -= RAD(360);
		}
	}
	else if (ang <= RAD(0)) {
		while (ang <= RAD(0)) {
			ang += RAD(360);
		}
	}

}

#define ThisForEachVec(vec)\
	for(auto& i : vec)


union constant {
	//Value holders
	int i;
	float f;

	//Operators and stuff
	const constant() {};
	constexpr constant(float a) : f(a) {}
	constexpr constant(double a) : f(float(a)) {}
	constexpr constant(int a) : i(a) {}
	constexpr constant(uint32_t a) : i(a) {}
	constexpr constant(uint16_t a) : i(a) {}
	constexpr constant(uint8_t a) : i(a) {}

	//Float stuff
	constexpr operator float() { return f; }
	constexpr operator double() { return double(f); }

	//Int stuff
	constexpr operator int() { return i; }
	constexpr operator uint32_t() { return uint32_t(i); }
	constexpr operator uint16_t() { return uint16_t(i); }
	constexpr operator uint8_t() { return uint8_t(i); }
};