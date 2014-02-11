#ifndef PLAYER_H
#define PLAYER_H
#include <Ogre.h>
#include "Block.h"
#include <string.h>
#include <string>
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
	Ogre::Vector3 acceleration;
	double m_speed;
	int score;
	int deaths;
	double m_mass;
	Ogre::Degree roll;//the players tilt
	void update(double timePassed);
	Ogre::Vector3 getBlock();//check which block the player is currently inside of. the one below decides direction and speed incriment, the one in front may be an obstacle
	void setJump();//STREIGHT_UP, LEFT_RAIL, RIGHT_RAIL
	vector<Block> & r_Map;
	Ogre::Vector3 overBlock();
	void setLean(std::string direction);
	void stopLean();
	Ogre::Quaternion getOrientation();
	bool jumping;//if this is true, the player is in the middle of a jump;
	Ogre::Vector3 getDirection();
	Ogre::Vector3 GetPosition();
	//side jumping vars
	bool m_isSideJumping;
	void sideJump(std::string jumpWhere);
	float m_AmountToSideJump;
	float m_JumpPerSecond;
	void changeRail(float timePassed);
	bool m_fallenOff;
	int blockOverId();
	void setPosition(Ogre::Vector3 posIn);
	

private:
	 
	double getSpeedMod();
	
	float getOptimumRoll();
	Ogre::Entity * mEntity;
	Ogre::SceneNode *mNode;
	Ogre::SceneManager *mSceneMgr;
	Ogre::Radian m_Angle;
	Ogre::Vector3 m_jumpingIn;
	
	int vect32BlockID(Ogre::Vector3);
	Ogre::Vector3 m_position;

	
	float jumpforce;
	//float horozontalJumpPerFrame;
	void lean();
	bool leanBack;
};
#endif