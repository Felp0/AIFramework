#pragma once

#include "WaypointManager.h"

using namespace std;

class Vehicle;
class PickupItem;
typedef vector<PickupItem*> vecPickups;

#define MAX_DISTANCE = 5.0f

std::unordered_map<Waypoint*, Waypoint*> wayMap;

typedef std::pair<float, Waypoint*> costWay;

class AIManager
{
public:
	AIManager();
	virtual  ~AIManager();
	void	release();
	HRESULT initialise(ID3D11Device* pd3dDevice);
	void	update(const float fDeltaTime);
	void	mouseUp(int x, int y);
	void	keyDown(WPARAM param);
	void	keyUp(WPARAM param);
	void	behaviours(float fDeltatime);
	void	center();
	void	wanderBehaviour(float fDeltaTime);
	void	seekBehaviour(float fDeltaTime);
	void	fleeBehaviour(float fDeltaTime);
	void	pathfinding();

protected:
	bool	checkForCollisions();
	void	setRandomPickupPosition(PickupItem* pickup);
	

private:
	vecPickups              m_pickups;
	Vehicle*				m_pCar = nullptr;
	Vehicle*				m_pSecondCar = nullptr;
	WaypointManager			m_waypointManager;

	bool					m_wandering;
	bool					m_seeking;
	bool					m_fleeing;
	bool					m_check;
	
	float					m_timer;
	float					m_elapsedTime;
	float					m_maxDistance ;

	Vector2D				m_sterringVelocity;
	Vector2D				m_desiredVelocity;

};

