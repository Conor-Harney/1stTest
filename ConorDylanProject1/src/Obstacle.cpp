#include "Obstacle.h"
#include <math.h>
Obstacle::Obstacle()
{

}

Obstacle::Obstacle(Ogre::SceneNode *object, Ogre::Vector3 pos, float width, float height, float depth):m_object(object), m_pos(pos), m_width(width), m_height(height), m_depth(depth), m_isVisible(true)
{

}

Obstacle::~Obstacle()
{
	delete(m_object);
}

Ogre::Vector3 Obstacle::ReturnPos()
{
	return m_pos;
}

bool Obstacle::IsHit(Ogre::Vector3 playerPos, float playerWidth, float playerHeight, float playerDepth)
{
	if(m_isVisible == true)
	{
		//if(playerPos.z+playerDepth<=m_pos.z+m_depth&&playerPos.y+playerHeight<=m_pos.y+m_height)
		if(Ogre::Math::Sqrt((playerPos.x - m_pos.x)*(playerPos.x - m_pos.x) + (playerPos.y - m_pos.y)*(playerPos.y - m_pos.y)+(playerPos.z - m_pos.z)*(playerPos.z - m_pos.z))<playerWidth/2 + m_depth/2)
		{
			m_isVisible = false;
			return true;
		}

		else
			return false;
	}

	else
		return false;
}

void Obstacle::Draw()
{

}

Ogre::Vector3 Obstacle::getPosition(){
	return m_pos;
}