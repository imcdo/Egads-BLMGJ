#pragma once
#include<glm/glm.hpp>

namespace Math{
	class Rect {
	private:
		glm::vec2 bl;
		glm::vec2 ur;
	public:
		Rect(glm::vec2 min, glm::vec2 max) :
			bl(min), ur(max) {}

		void Set(glm::vec2 min, glm::vec2 max) {
			bl = min;
			ur = ur;
		}

		glm::vec2 getCenter() const { return bl / 2.0f + ur / 2.0f; }

		float getHeight() const { return ur.y - bl.y; }

		float getWidth() const { return ur.x - bl.x; }

		glm::vec2 getMax() const { return ur; }

		glm::vec2 getMin() const { return bl; }

		float getXMin() const { return bl.x; }

		float getXMax() const { return ur.x; }

		float getYMin() const { return bl.y; }

		float getYMax() const { return ur.y; }

		// Strict contains
		bool Contains(Rect other) {
			return ur.x > other.ur.x && ur.y > other.ur.y 
				&& bl.x < other.bl.x && bl.y < other.bl.y;
		}
		bool Contains(glm::vec2 point) {
			return ur.x > point.x && ur.y > point.y
				&& bl.x < point.x&& bl.y < point.y;
		}

		// Strict Overlap
		bool Overlaps(Rect other) {
			return !(bl.x >= other.ur.x || ur.x <= other.bl.x
				|| bl.y >= other.ur.y || ur.y <= other.bl.y);
		}
	};
}