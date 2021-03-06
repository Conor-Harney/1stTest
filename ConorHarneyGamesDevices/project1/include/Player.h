#ifndef PLAYER_H
#define PLAYER_H
#include <Ogre.h>
#include "Block.h"
#include <vector>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

using std::vector;

class Player{
public:
	Player(Ogre::Vector3 posIn, Ogre::SceneManager *sceneMan, vector<Block> & mapIn, float sizeIn);
	Ogre::Vector3 dimentions;
	Ogre::Vector3 velocity;
	double acceleration;
	Ogre::Vector3 pos;
	double speed;
	int score;
	int deaths;
	Ogre::Degree roll;//the players tilt
	void update();
	Ogre::Vector3 getBlock();//check which block the player is currently inside of. the one below decides direction and speed incriment, the one in front may be an obstacle
	void setJump();
	vector<Block> & r_Map;
	Ogre::Vector3 overBlock();


private:
	
	double getSpeedMod();
	Ogre::Vector3 getDirection();
	float getOptimumRoll();
	Ogre::Entity * mEntity;
	Ogre::SceneNode *mNode;
	Ogre::SceneManager *mSceneMgr;
	
	int vect32BlockID(Ogre::Vector3);

	bool jumping;//if this is true, the player is in the middle of a jump;
	float jumpforce;
};
#endif