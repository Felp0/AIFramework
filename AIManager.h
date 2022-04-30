#pragma once

#include "WaypointManager.h"

using namespace std;

class Vehicle;
class PickupItem;
typedef vector<PickupItem*> vecPickups;

#define MAX_DISTANCE = 5.0f
#define MAX_SPEED = 5.0f

//std::unordered_map<Waypoint*, Waypoint*> wayMap;
//
//typedef std::pair<float, Waypoint*> costWay;

class AIManager
{
public:
	AIManager();
	virtual  ~AIManager();

	HRESULT initialise(ID3D11Device* pd3dDevice);

	void	release();
	void	update(const float fDeltaTime);
	void	mouseUp(int x, int y);
	void	keyDown(WPARAM param);
	void	keyUp(WPARAM param);
	void	behaviours(float fDeltatime);
	void	center();
	void	wanderBehaviour(float fDeltaTime);
	void	seekBehaviour();
	void	objAvoidance();
	void	pursuitBehaviour();
	void	fleeBehaviour();
	void	arriveBehaviour();
	void	pathfinding();

protected:
	bool	checkForCollisions();

	void	setRandomPickupPosition(PickupItem* pickup);
	

private:
	vecPickups              m_pickups;

	Vehicle*				m_pCar = nullptr;
	Vehicle*				m_pSecondCar = nullptr;

	Waypoint*				m_randomWaypoint;

	WaypointManager			m_waypointManager;

	bool					m_wandering;
	bool					m_seeking;
	bool					m_fleeing;
	bool					m_check;
	bool					m_pursuit;
	bool					m_arrived;
	bool					m_avoidObj;
	
	float					m_timer;
	float					m_elapsedTime;
	float					m_maxDistance ;
	float					m_slowRadius;
	float					m_distance;
	float					m_circleDistance;
	float					m_circleRadius;
	float					m_fleeRadius;

	Vector2D				m_sterringVelocity;
	Vector2D				m_desiredVelocity;
	Vector2D				m_fleeVelocity;
	Vector2D				m_velocity;
	Vector2D				m_futurePoint;
	
	

};

