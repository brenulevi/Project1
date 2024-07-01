#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
	m_fov = FOV;
	m_nearPlane = NEAR_PLANE;
	m_farPlane = FAR_PLANE;

	m_view = mat4(1.0f);
	m_projection = mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::initialize()
{
	auto& wnd = Game::GetInstance()->getWindow();
	float aspect = (float)wnd.getWidth() / (float)wnd.getHeight();

	m_projection = perspective(radians(m_fov), aspect, m_nearPlane, m_farPlane);
	auto& shader = Game::GetInstance()->getShader();
	shader.setMat4("projection", m_projection);

	wnd.setViewport();
}

void Camera::update(vec3 playerPosition, vec3 playerForward, vec3 playerRight)
{
	m_view = lookAt(playerPosition, playerPosition + playerForward, vec3(0, 1, 0));
	auto& shader = Game::GetInstance()->getShader();
	shader.setMat4("view", m_view);
}
