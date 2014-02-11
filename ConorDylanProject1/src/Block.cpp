#include "Block.h"

Block::Block(Ogre::Vector3 blockVecIn, Ogre::Vector3 posIn, Ogre::Vector3 directionIn):blockVec(blockVecIn), pos(posIn), mSpeedMod(0.0001), mDirection(directionIn){}

void Block::initilise(Ogre::SceneManager *sceneMan, Block::Block_Type typeOfBlock){
	blockType = typeOfBlock;
	mSceneMgr = (sceneMan);// ,score(0), deaths(0), velocity(Ogre::Vector3(0,0,0)), acceleration(Ogre::Vector3(0,0,0)), pos(posIn), jumping(false), r_Map(mapIn){
	blockName = "Block ";// + " " + static_cast<char>(blockVec.y) + " "+ static_cast<char>(blockVec.z); 
	
	std::ostringstream convert; 
	convert << "<" << blockVec.x << "-" << blockVec.y << "-" << blockVec.z << ">"; 

	blockName = blockName + convert.str();

	Ogre::String meshName  = "streightRail.mesh";
	if (blockType == Block_Type::streightRaill)
	{
		meshName = "streightRail.mesh";
	}
	else if(blockType == Block_Type::curvedRail)
	{
		meshName = "curvedRail2.mesh";
	}

	mEntity = mSceneMgr->createEntity(blockName, meshName);
    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	if(blockType != Block_Type::null){
		mNode->attachObject(mEntity);
	}
	mNode->setPosition(pos);
	//mNode->scale(0.5f, 0.5f, 0.5f);
	
	mNode->scale(25.0f, 75.0f, 25.0f);
	if(blockType == Block_Type::streightRaill){
		mNode->yaw(Ogre::Radian(Ogre::Math::HALF_PI), mNode->TS_LOCAL);

		///////////////////////////////
		int i = (blockVec.x + blockVec.y + blockVec.z);
		if (i % 2 == 0){
			//mNode->pitch(Ogre::Radian(0.5));
		}
		/////////////////////////////

		mNode->yaw(Ogre::Radian(Ogre::Math::HALF_PI * mDirection.x), mNode->TS_LOCAL);
	}
	else if(blockType == Block_Type::curvedRail){
		mNode->yaw(Ogre::Radian(Ogre::Math::HALF_PI * 3), mNode->TS_LOCAL);
	}
	
}

double Block::getSpeedMod(){
	return mSpeedMod;
}

Ogre::Vector3 Block::getDirection(){
	if(blockType != Block_Type::null){
		return mDirection;
	}
	else{
		return Ogre::Vector3(0,-1,0);
	}
}

float Block::getTop(){
	return pos.y + (size / 2);
}

void Block::setObjectToCenter(Ogre::Vector3 * objPosPtr){
	if (blockType == Block_Type::streightRaill)
	{
		if(mDirection == Ogre::Vector3(1,0,0) || mDirection == Ogre::Vector3(-1,0,0)){
			objPosPtr->z = pos.z + (size / 2);
		}
		else if(mDirection == Ogre::Vector3(0,0,1) || mDirection == Ogre::Vector3(0,0,-1)){
			Ogre::Real xpos = pos.x + (size / 2);
			objPosPtr->x = pos.x + (size / 2);
		}
	}
}