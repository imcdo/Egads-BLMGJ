#pragma once
#include<glm/glm.hpp>

namespace Math{
	class Rect {
	private:
		glm::vec2 bl;
		glm::vec2 ur;
	public:
		Rect(glm::vec2 min, glm::vec2 max);

		void Set(glm::vec2 min, glm::vec2 max);

		glm::vec2 getCenter() const;

		float getHeight() const;

		float getWidth() const;

		glm::vec2 getMax() const;

		glm::vec2 getMin() const;

		float getXMin() const;

		float getXMax() const;

		float getYMin() const;

		float getYMax() const;

		// Strict contains
		bool Contains(Rect other);

		bool Contains(glm::vec2 point);

		// Strict Overlap
		bool Overlaps(Rect other);
	};
	float angleBetween(glm::vec2 a, glm::vec2 b);

}