#ifndef __Obstacle_h_
#define __Obstacle_h_

#include "BaseApplication.h"

class Obstacle
{
public:
	Obstacle();
	Obstacle(Ogre::SceneNode *object, Ogre::Vector3 pos, float width, float height, float depth);
	~Obstacle(void);

	Ogre::Vector3 ReturnPos();
	bool IsHit(Ogre::Vector3 playerPos, float playerWidth, float playerHeight, float playerDepth);
	Ogre::Vector3 getPosition();
	void Draw();

private:
	Ogre::Vector3 m_pos;
	Ogre::SceneNode *m_object;
	
	float m_height;
	float m_width;
	float m_depth;

	float m_isVisible;
};

#endif