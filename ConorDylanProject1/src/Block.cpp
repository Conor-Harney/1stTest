#include "Block.h"

Block::Block(Ogre::Vector3 blockVecIn, Ogre::Vector3 posIn):blockVec(blockVecIn), pos(posIn), mSpeedMod(0), mDirection(Ogre::Vector3(0,0,1)){}

void Block::initilise(Ogre::SceneManager *sceneMan, Block::Block_Type typeOfBlock){
	blockType = typeOfBlock;
	mSceneMgr = (sceneMan);// ,score(0), deaths(0), velocity(Ogre::Vector3(0,0,0)), acceleration(Ogre::Vector3(0,0,0)), pos(posIn), jumping(false), r_Map(mapIn){
	blockName = "Block ";// + " " + static_cast<char>(blockVec.y) + " "+ static_cast<char>(blockVec.z); 
	
	std::ostringstream convert; 
	convert << "<" << blockVec.x << "-" << blockVec.y << "-" << blockVec.z << ">"; 

	blockName = blockName + convert.str();


	mEntity = mSceneMgr->createEntity(blockName, "cube.mesh");
    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	if(blockType != Block_Type::null){
		mNode->attachObject(mEntity);
	}
	mNode->setPosition(pos);
	mNode->scale(0.5f, 0.5f, 0.5f);
	int i = (blockVec.x + blockVec.y + blockVec.z);
	if (i % 2 == 0){
		//mNode->pitch(Ogre::Radian(0.5));
	}
	if(blockVec.z == 9)
	{mDirection = Ogre::Vector3(1,0,0);}
}

double Block::getSpeedMod(){
	return mSpeedMod;
}

Ogre::Vector3 Block::getDirection(){
	return mDirection;
}

float Block::getTop(){
	return pos.y + (size / 2);
}