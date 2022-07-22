#pragma once
#include"Base.h"

enum class CAMERA_MOVE
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FRONT,
	MOVE_BACK
};
class Camera
{
private:
	glm::vec3	m_position;
	glm::vec3	m_front;
	glm::vec3	m_up;
	float		m_speed;

	float		m_pitch;
	float		m_yaw;
	float		m_sensitivity;

	float		m_xpos;
	float       m_ypos;
	bool		m_firstMove;

	glm::mat4	m_vMatrix;
public:
	Camera()
	{
		m_position = glm::vec3(1.0f);
		m_front = glm::vec3(1.0f);
		m_up = glm::vec3(1.0f);
		m_speed = 0.01f;

		m_pitch = 0.0f;
		m_yaw = -90.0f;
		m_sensitivity = 0.1f;

		m_xpos = 0;
		m_ypos = 0;
		m_firstMove = true;

		m_vMatrix = glm::mat4(1.0f);
	}
	~Camera()
	{

	}
	void lookAt(glm::vec3 _pos , glm::vec3 _front , glm::vec3 _up );
	void update();

	glm::mat4 getMatrix();
	glm::vec3 getPosition();
	glm::vec3 getDirection();

	void	setSpeed(float _speed)
	{
		m_speed = _speed;
	}

	void move(CAMERA_MOVE _mode);

	void pitch(float _yOffset);
	void yaw(float _xOffset);
	void setSentitivity(float _s);
	void onMouseMove(double _xpos , double _ypos);
};

