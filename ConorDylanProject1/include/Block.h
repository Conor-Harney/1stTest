#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <Ogre.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <math.h>

class Block{

public:
	enum Block_Type{ null, streightRaill, curvedRail, gradientRail};
	static const int size = 50;
	Block(Ogre::Vector3 blockVecIn, Ogre::Vector3 posIn, Ogre::Vector3 directionIn);
	void initilise(Ogre::SceneManager *sceneMan, Block::Block_Type typeOfBlock);
	double getSpeedMod();
	Ogre::Vector3 getDirection();
	std::string blockName;
	float getTop();
	Block_Type blockType;
	void setObjectToCenter(Ogre::Vector3 * objPosPtr);

protected:
	
	
	Ogre::Vector3 blockVec;//the x, y and z number of the block 
	Ogre::Vector3 pos;
	//static const Ogre::Vector3 dimensions = Ogre::Vector3(50, 50, 50);//length, breadth and height
	
	
private:
	Ogre::Entity * mEntity;
	Ogre::SceneNode *mNode;
	double mSpeedMod;
	Ogre::Vector3 mDirection;
	Ogre::SceneManager *mSceneMgr;
	

};

#endif