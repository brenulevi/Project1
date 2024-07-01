#pragma once

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Ray
{
public:
	Ray(vec3 origin, vec3 direction);
	~Ray();

	vec3 getOrigin() const { return m_origin; }
	vec3 getPrevious() const { return m_previous; }
	vec3 getEnd() const { return m_end; }
	vec3 getDirection() const { return m_direction; }
	float getLength() const { return glm::length(m_end - m_origin); }

	void step();

private:
	vec3 m_origin;
	vec3 m_previous;
	vec3 m_end;
	vec3 m_direction;
};

