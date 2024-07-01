#pragma once

#include "Transform.h"
#include "Camera.h"

constexpr float PLAYER_SPEED = 30.0f;
constexpr int PLAYER_HEIGHT = 2;
constexpr int INTERACTION_DISTANCE = 5;
constexpr float VIEW_X_MAX = 89.0f;
constexpr float VIEW_SPEED = 0.1f;

class Player
{
public:
	Player();
	~Player();

	void initialize();
	void update();

	Transform& getTransform() { return m_transform; }
	Camera& getCamera() { return m_camera; }

private:
	Transform m_transform;
	Camera m_camera;
};

