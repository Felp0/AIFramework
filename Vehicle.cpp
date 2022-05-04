#include "Vehicle.h"
#include "PickupItem.h"

#define NORMAL_MAX_SPEED 100
#define MAX_SPEED 300

#define SPEED 5


HRESULT	Vehicle::initMesh(ID3D11Device* pd3dDevice, carColour colour)
{
	m_scale = XMFLOAT3(30, 20, 1);

	if (colour == carColour::redCar)
	{
		setTextureName(L"Resources\\car_red.dds");
	}
	if (colour == carColour::blueCar)
	{
		setTextureName(L"Resources\\car_blue.dds");
	}

	HRESULT hr = DrawableGameObject::initMesh(pd3dDevice);

	m_maxSpeed = NORMAL_MAX_SPEED;
	m_mass = 5.0f;
	m_currentSpeed = m_maxSpeed;
	m_fuel = 100.0f;

	setVehiclePosition(Vector2D(0, 0));
	setMaxSpeed(MAX_SPEED);


	m_lastPosition = Vector2D(0, 0);

	m_arrived = true;
	m_picked = true;

	

	return hr;
}

void Vehicle::update(const float deltaTime)
{
	// consider replacing with force based acceleration / velocity calculations
	//Vector2D vecTo = m_positionTo - m_currentPosition;
	//float velocity = deltaTime * m_currentSpeed;

	//float length = (float)vecTo.Length();
	//// if the distance to the end point is less than the car would move, then only move that distance. 
	//if (length > 0) {
	//	vecTo.Normalize();
	//	if(length > velocity)
	//		vecTo *= velocity;
	//	else
	//		vecTo *= length;

	//	m_currentPosition += vecTo;
	//}

	//getAcceleration(Vector2D(10,0));

	//moving with Physics

	switch (m_currentState)
	{
	case carState::pathfinding:
		{
			if(m_picked)
			{
				pathToWaypoint(m_waypointManager->getNearestWaypoint(m_passenger->getPosition()));
				m_picked = false;
			}
			else
			{

				travessingVector();
			}
			break;
		}
	default:
		break;
	}
	m_velocity = m_velocity + m_acceleration;
	m_velocity.Truncate(SPEED);
	
	m_currentPosition = m_currentPosition + m_velocity;


	// rotate the object based on its last & current position
	Vector2D diff = m_currentPosition - m_lastPosition;
	if (diff.Length() > 0) { // if zero then don't update rotation
		diff.Normalize();
		m_radianRotation = atan2f((float)diff.y, (float)diff.x); // this is used by DrawableGameObject to set the rotation
	}
	m_lastPosition = m_currentPosition;

	// set the current poistion for the drawablegameobject
	setPosition(Vector2D(m_currentPosition));

	DrawableGameObject::update(deltaTime);
}


// a ratio: a value between 0 and 1 (1 being max speed)
void Vehicle::setCurrentSpeed(const float speed)
{
	m_currentSpeed = m_maxSpeed * speed;
	m_currentSpeed = max(0, m_currentSpeed);
	m_currentSpeed = min(1, m_currentSpeed);
}

// set a position to move to
void Vehicle::setPositionTo(Vector2D position)
{
	m_startPosition = m_currentPosition;
	
	m_positionTo = position;
}

// set the current position
void Vehicle::setVehiclePosition(Vector2D position)
{
	m_currentPosition = position;
	m_positionTo = position;
	m_startPosition = position;
	setPosition(position);
}

void Vehicle::setWaypointManager(WaypointManager* wpm)
{
	m_waypointManager = wpm;
}

void Vehicle::setPickup(PickupItem* passenger)
{
	m_passenger = passenger;
}

void Vehicle::setVelocity(Vector2D velocity)
{
	m_velocity = velocity;
}

void Vehicle::pathToWaypoint(Waypoint* goWaypoint)
{

	// current node wp = waypoint calculate g cost, h cost, f cost
	Node* currentNode = new Node();
	currentNode->wp = goWaypoint;
	currentNode->gCost = m_currentPosition.Distance(goWaypoint->getPosition());

	_vWp.clear();
	

	// while node.wp is not car.wp
	while (currentNode->wp != m_waypointManager->getNearestWaypoint(m_currentPosition))
	{
		_vWp.push_back(currentNode->wp);
		currentNode = findClosestNeighbour(currentNode->wp, goWaypoint); 
	}

	_vWp.push_back(currentNode->wp);

	// get niehgbours

}

void Vehicle::travessingVector()
{
	if (m_arrived)//if u arrived generate a new path
	{
		Waypoint* wp = _vWp.back();
		Vector2D Direction = wp->getPosition() - m_currentPosition;
		Direction.Normalize();

		m_velocity = Direction;
		m_arrived = false;
	}
	else
	{
		if (m_currentPosition.Distance(_vWp.back()->getPosition()) <= 0.5f)
		{
			_vWp.pop_back();
			m_arrived = true;
		}
	}

	
}

Node* Vehicle::findClosestNeighbour(Waypoint* wp, Waypoint* endNode)
{
	vecWaypoints neighbour = m_waypointManager->getNeighbouringWaypoints(wp);
	Node* closetNode = new Node();
	Node* currentNode = new Node();
	closetNode->gCost = 99999;

	for (int i = 0; i < neighbour.size(); i++)
	{
		currentNode->wp = neighbour[i];
		currentNode->gCost = neighbour[i]->getPosition().Distance(m_currentPosition);

		if (closetNode->gCost > currentNode->gCost)
		{
			closetNode->wp = currentNode->wp;
			closetNode->gCost = currentNode->gCost;
		}
	}


	return closetNode;
}


