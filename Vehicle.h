#pragma once

#include "DrawableGameObject.h"
#include "WaypointManager.h"
#include "Vector2D.h"
#include "Collidable.h"


enum class carColour
{
	redCar,
	blueCar,
};

class Vehicle : public DrawableGameObject, public Collidable
{
public:
	virtual HRESULT initMesh(ID3D11Device* pd3dDevice, carColour colour);
	virtual void update(const float deltaTime);

	void setMaxSpeed(const float maxSpeed) { m_maxSpeed = maxSpeed; }
	void setCurrentSpeed(const float speed); // a ratio: a value between 0 and 1 (1 being max speed)
	void setPositionTo(Vector2D positionTo); // a position to move to
	void setVehiclePosition(Vector2D position); // the current position - this resets positionTo
	void setWaypointManager(WaypointManager* wpm);
	void setVelocity(Vector2D velocity);
	void hasCollided() {}

	Vector2D getVelocity() { return m_velocity; }
	Vector2D getPositionTo() { return m_positionTo; }
	Vector2D getCurrentPosition() { return m_currentPosition; }
	float getCurrentSpeed() { return m_currentSpeed; }
	float getMaxSpeed() { return m_maxSpeed; }

	void getAcceleration(Vector2D force) { m_acceleration = force / m_mass;}
	
	//void addForce(Vector2D force);





protected: // protected methods


protected: // preotected properties
	float				m_maxSpeed;
	float				m_currentSpeed;
	float				m_mass;


	Vector2D			m_velocity;
	Vector2D			m_currentPosition;
	Vector2D			m_startPosition;
	Vector2D			m_positionTo;
	Vector2D			m_acceleration;
	Vector2D			m_lastPosition;

	WaypointManager*	m_waypointManager;

};

