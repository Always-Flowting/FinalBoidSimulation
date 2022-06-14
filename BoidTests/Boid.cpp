#include "Boid.h"

std::mt19937 Boid::m_rand{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
std::uniform_real_distribution<float> Boid::randomAngle{ 0.0f, 6.283185f };

// default constructor for a boid object
Boid::Boid()
	:m_position{ glm::vec2{0.0f, 0.0f} },
	m_maxAcceleration{ 0.0f },
	m_maxVelocity{ 0.0f },
	m_senseDistance{ 0.0f },
	m_seperationDistance{ 0.0f },
	m_size{ 0.0f },
	m_type{ Type::prey }
{ }

// constructor for a boid object will give the boid a random direction to face
Boid::Boid(const glm::vec2& position, float maxAccel, float maxVel, float sense, float seperation, float size, Type type)
	:m_position{ position },
	m_maxAcceleration{ maxAccel },
	m_maxVelocity{ maxVel },
	m_senseDistance{ sense },
	m_seperationDistance{ seperation },
	m_size{ size },
	m_type{ type }
{
	float angle{ randomAngle(m_rand) };
	m_velocity = m_maxVelocity * glm::vec2(glm::cos(angle), glm::sin(angle));
}

// upate the boids velocity and position then reset the acceleration
void Boid::update()
{
	if (glm::length(m_acceleration) > m_maxAcceleration)
	{
		m_acceleration = glm::normalize(m_acceleration) * m_maxAcceleration;
	}
	m_velocity += m_acceleration;

	if (glm::length(m_velocity) > m_maxVelocity)
	{
		m_velocity = glm::normalize(m_velocity) * m_maxVelocity;
	}
	m_position += m_velocity;

	m_acceleration = glm::vec2{ 0.0f };
}