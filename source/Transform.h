#pragma once

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform
{
public:
	Transform();
	~Transform();

	void update();

	mat4 getModel();

	void translate(const vec3& translation);
	void rotate(const vec3& rotation);

	vec3 inverseTransformPoint(vec3 point);

public:
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_scale;
	vec3 m_forward;
	vec3 m_right;
	vec3 m_up;

private:
	mat4 m_model;
};

