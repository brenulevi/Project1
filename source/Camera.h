#pragma once

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

constexpr float FOV = 60.0f;
constexpr float NEAR_PLANE = 0.1f;
constexpr float FAR_PLANE = 1000.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void initialize();
	void update(vec3 playerPosition, vec3 playerForward, vec3 playerRight);

private:
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	mat4 m_projection;
	mat4 m_view;
};

