#include "Transform.h"

Transform::Transform()
{
	m_position = vec3(0.0f, 0.0f, 0.0f);
	m_rotation = vec3(0.0f, 0.0f, 0.0f);
	m_scale = vec3(1.0f, 1.0f, 1.0f);
	m_forward = vec3(0.0f, 0.0f, 1.0f);
	m_right = vec3(1.0f, 0.0f, 0.0f);
	m_up = vec3(0.0f, 1.0f, 0.0f);

	m_model = mat4(1.0f);
}

Transform::~Transform()
{
}

void Transform::update()
{
	vec3 fwrd = { 0.0f, 0.0f, 0.0f };
	fwrd.x = cos(radians(m_rotation.y + 90.0f)) * cos(radians(m_rotation.x));
	fwrd.y = sin(radians(m_rotation.x));
	fwrd.z = sin(radians(m_rotation.y + 90.0f)) * cos(radians(m_rotation.x));
	m_forward = normalize(fwrd);

	m_right = normalize(cross(m_forward, vec3(0.0f, 1.0f, 0.0f)));
	m_up = normalize(cross(m_right, m_forward));
}

mat4 Transform::getModel()
{	
	m_model = mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::rotate(m_model, radians(m_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	m_model = glm::rotate(m_model, radians(m_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	m_model = glm::rotate(m_model, radians(m_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	m_model = glm::scale(m_model, m_scale);

	return m_model;
}

void Transform::translate(const vec3& translation)
{
	m_position += translation;
}

void Transform::rotate(const vec3& rotation)
{
	m_rotation += rotation;
}

vec3 Transform::inverseTransformPoint(vec3 point)
{
    return glm::inverse(getModel()) * vec4(point, 1.0f);
}
