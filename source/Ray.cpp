#include "Ray.h"

Ray::Ray(vec3 origin, vec3 rotation)
{
	m_origin = origin;
	m_previous = origin;

	float yaw = glm::radians(rotation.y + 90);
	float pitch = glm::radians(rotation.x);
	float x = glm::cos(yaw) * glm::cos(pitch);
	float y = glm::sin(pitch);
	float z = glm::cos(pitch) * glm::sin(yaw);
	m_direction = { x, y, z };

	m_end = m_origin;
}

Ray::~Ray()
{
}

void Ray::step()
{
	m_previous = m_end;
	m_end += m_direction / 4.0f;
}
