#include "math.h"
#include <iostream>

Math::Rect::Rect(glm::vec2 min, glm::vec2 max) :
	bl(min), ur(max) {}

void Math::Rect::Set(glm::vec2 min, glm::vec2 max) {
	bl = min;
	ur = ur;
}

glm::vec2 Math::Rect::getCenter() const { return bl / 2.0f + ur / 2.0f; }

float Math::Rect::getHeight() const { return ur.y - bl.y; }

float Math::Rect::getWidth() const { return ur.x - bl.x; }

glm::vec2 Math::Rect::getMax() const { return ur; }

glm::vec2 Math::Rect::getMin() const { return bl; }

float Math::Rect::getXMin() const { return bl.x; }

float Math::Rect::getXMax() const { return ur.x; }

float Math::Rect::getYMin() const { return bl.y; }

float Math::Rect::getYMax() const { return ur.y; }

// Strict contains
bool Math::Rect::Contains(Rect other) {
	return ur.x > other.ur.x && ur.y > other.ur.y
		&& bl.x < other.bl.x&& bl.y < other.bl.y;
}
bool Math::Rect::Contains(glm::vec2 point) {
	return ur.x > point.x && ur.y > point.y
		&& bl.x < point.x&& bl.y < point.y;
}

// Strict Overlap
bool Math::Rect::Overlaps(Rect other) {
	return !(bl.x >= other.ur.x || ur.x <= other.bl.x
		|| bl.y >= other.ur.y || ur.y <= other.bl.y);
}

float Math::angleBetween(glm::vec2 a, glm::vec2 b) {
	a = glm::normalize(a);
	b = glm::normalize(b);
	/*float atb = glm::atan(b.y, b.x);
	float ata = glm::atan(a.y, a.x);
	float angle = (atb * atb - ata * ata);*/
	
	float angle = glm::degrees(glm::acos(glm::dot(a, b)));

	if (a.x * b.y - a.y * b.x < 0)
		angle = -angle;
	
	std::cout << "angle: " << angle << std::endl;
	return angle;
}