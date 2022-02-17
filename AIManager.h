#pragma once

#include "WaypointManager.h"

using namespace std;

class Vehicle;
class PickupItem;
typedef vector<PickupItem*> vecPickups;

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
	void	center();
	void	wanderBehaviour(float fDeltaTime);
	void	seekBehaviour(float fDeltaTime);

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
	
	float					m_timer;
	float					m_elapsedTime;

};

