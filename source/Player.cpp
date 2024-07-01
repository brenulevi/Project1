#include "Player.h"
#include "Input.h"
#include "Game.h"
#include <iostream>
#include "Ray.h"

Player::Player()
{
	m_transform = Transform();
	m_camera = Camera();
}

Player::~Player()
{
}

void Player::initialize()
{
	m_camera.initialize();
}

void Player::update()
{
	m_transform.update();
	m_camera.update(m_transform.m_position, m_transform.m_forward, m_transform.m_right);

	vec3 moveDir = vec3(0.0f);

	vec3 forward = m_transform.m_forward;
	forward.y = 0.0f;
	forward = normalize(forward);

	if (Input::isKeyHeld(VK_W))
		moveDir += forward;
	if (Input::isKeyHeld(VK_S))
		moveDir -= forward;
	if (Input::isKeyHeld(VK_A))
		moveDir -= m_transform.m_right;
	if (Input::isKeyHeld(VK_D))
		moveDir += m_transform.m_right;
	if (Input::isKeyHeld(VK_SPACE))
		moveDir += vec3(0, 1, 0);
	if (Input::isKeyHeld(VK_SHIFT))
		moveDir -= vec3(0, 1, 0);

	if (length(moveDir) > 0.0f)
	{
		moveDir = normalize(moveDir);
		m_transform.translate(moveDir * PLAYER_SPEED * Game::GetInstance()->getTimer().getDeltaTime());
	}

	int deltaX = Input::getMouseDeltaX();
	int deltaY = Input::getMouseDeltaY();
	
	m_transform.rotate(vec3(-deltaY * VIEW_SPEED, deltaX * VIEW_SPEED, 0.0f));

	if (m_transform.m_rotation.x > VIEW_X_MAX)
		m_transform.m_rotation.x = VIEW_X_MAX;
	if (m_transform.m_rotation.x < -VIEW_X_MAX)
		m_transform.m_rotation.x = -VIEW_X_MAX;

	if (Input::isKeyPressed(VK_P))
	{
		if (Game::GetInstance()->getWindow().getPolygonMode() == SOLID)
			Game::GetInstance()->getWindow().setPolygonMode(WIREFRAME);
		else
			Game::GetInstance()->getWindow().setPolygonMode(SOLID);
	}

	std::cout << m_transform.m_position.x << " " << m_transform.m_position.y << " " << m_transform.m_position.z << std::endl;

	if (Input::isMouseKeyPressed(VK_LBUTTON) || Input::isMouseKeyPressed(VK_RBUTTON))
	{
		Ray ray = Ray(m_transform.m_position, m_transform.m_rotation);
		for (; ray.getLength() < INTERACTION_DISTANCE; ray.step())
		{
			auto targetChunk = Game::GetInstance()->getWorld().getChunkAt(ray.getEnd());
			if (targetChunk)
			{
				auto blockIndex = targetChunk->getTransform().inverseTransformPoint(ray.getEnd());
				auto blockType = targetChunk->getBlockTypeAt(blockIndex);
				if (blockType != BlockType::AIR)
				{
					targetChunk->setBlockTypeAt(blockIndex, BlockType::AIR);
					targetChunk->regenerateMesh();
					break;
				}
			}
		}

	}
		
	/*if (Input::isMouseKeyPressed(VK_LBUTTON))
	{
		Ray ray = Ray(m_transform.m_position, m_transform.m_forward);
		for (; ray.getLength() < INTERACTION_DISTANCE; ray.step())
		{
			vec3 rayBlock;
			rayBlock.x = floor(ray.getEnd().x);
			rayBlock.y = floor(ray.getEnd().y);
			rayBlock.z = floor(ray.getEnd().z);

			auto targetChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock);
			if (targetChunk)
			{
				auto blockIndex = targetChunk->getTransform().inverseTransformPoint(rayBlock);
				auto blockType = targetChunk->getBlockTypeAt(blockIndex);
				if (blockType != BlockType::AIR)
				{
					targetChunk->setBlockTypeAt(blockIndex, BlockType::AIR);
					targetChunk->regenerateMesh();

					if (blockIndex.x == 0)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock - vec3(1, 0, 0));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}
					else if (blockIndex.x == CHUNK_SIZE.x - 1)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock + vec3(1, 0, 0));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}

					if (blockIndex.y == 0)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock - vec3(0, 1, 0));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}
					else if (blockIndex.y == CHUNK_SIZE.y - 1)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock + vec3(0, 1, 0));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}

					if (blockIndex.z == 0)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock - vec3(0, 0, 1));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}
					else if (blockIndex.z == CHUNK_SIZE.z - 1)
					{
						auto neighborChunk = Game::GetInstance()->getWorld().getChunkAt(rayBlock + vec3(0, 0, 1));
						if (neighborChunk)
							neighborChunk->regenerateMesh();
					}

					break;
				}
			}
		}
	}*/

	/*if (Input::isMouseKeyPressed(VK_RBUTTON))
	{
		Ray ray = Ray(m_transform.m_position, m_transform.m_forward);
		for (; ray.getLength() <= INTERACTION_DISTANCE; ray.step())
		{
			vec3 rayBlock = floor(ray.getEnd());
			
			std::cout << rayBlock.x << " " << rayBlock.y << " " << rayBlock.z << std::endl;
		}
	}*/
}
