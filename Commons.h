#pragma once
#include <SFML\Graphics.hpp>
#include <stack>

#define PI 3.1415926535897932384626433832795
#define RAD(x) x * PI / 180

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

inline void drawRect(float x, float y, float w, float h, float dir, sf::Color c, sf::RenderWindow* target) {
	sf::RectangleShape rect(sf::Vector2f(w, h));

	w = fabs(w);
	h = fabs(h);

	rect.setRotation(dir * 180 / PI);
	rect.setOutlineColor(c);
	rect.setOrigin(w/2, h/2);
	rect.setPosition(sf::Vector2f(x, y));

	target->draw(rect);
}


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