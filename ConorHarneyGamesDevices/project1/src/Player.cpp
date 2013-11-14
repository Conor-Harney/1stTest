#include "Player.h"

Player::Player(Ogre::Vector3 posIn, Ogre::SceneManager *sceneMan, vector<Block> & mapIn, float sizeIn): 
	mSceneMgr(sceneMan) ,score(0), deaths(0), velocity(Ogre::Vector3(0,0,0)), acceleration(0), pos(posIn), jumping(false), r_Map(mapIn), speed(0.1), dimentions(Ogre::Vector3(sizeIn, sizeIn, sizeIn)){
	mEntity = mSceneMgr->createEntity("Player", "Sphere.mesh");
    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->setPosition(posIn);
	float modelSize = 200;
	mNode->scale(sizeIn / modelSize, sizeIn / modelSize, sizeIn / modelSize);
	mNode->yaw(Ogre::Radian(3.14159f), Ogre::Node::TransformSpace(0));
}



Ogre::Vector3 Player::getBlock(){
	Ogre::Vector3 blockIn;
	blockIn = Ogre::Vector3(pos.x / Block::size, pos.y / Block::size, pos.z / Block::size);
	return blockIn;
}

double Player::getSpeedMod(){
	
	double retSpeed = 0;

	if(getBlock().y >0){
	Ogre::Vector3 tempBlockOn = getBlock();
	tempBlockOn.x = (static_cast<int>(tempBlockOn.x));
	tempBlockOn.y = (static_cast<int>(tempBlockOn.y) -1);
	tempBlockOn.z = (static_cast<int>(tempBlockOn.z));
	int vectBlockNum = ((tempBlockOn.z * 100) + (tempBlockOn.y * 10) + tempBlockOn.x);
	if(pos.z >50){
			int breaker = 1;
		}
	retSpeed = r_Map[vectBlockNum].getSpeedMod();
	}

	return retSpeed;
}

Ogre::Vector3 Player::getDirection(){
	Ogre::Vector3 retDirect = Ogre::Vector3(0,0,1);

	if(getBlock().y > 0){
	Ogre::Vector3 tempBlockOn = getBlock();
	tempBlockOn.x = (static_cast<int>(tempBlockOn.x));
	tempBlockOn.y = (static_cast<int>(tempBlockOn.y) -1);
	tempBlockOn.z = (static_cast<int>(tempBlockOn.z));
	int vectBlockNum = ((tempBlockOn.x * 100) + (tempBlockOn.y * 10) + tempBlockOn.z);
	retDirect = r_Map[vectBlockNum].getDirection();

	}
	
	return retDirect;
}

float Player::getOptimumRoll(){
	return 0.0f;
}

void Player::update(){
	
	acceleration = getSpeedMod();

	if (jumping == true)
	{
		jumpforce -= 0.0981 / 40;//gravity / fps
		pos.y += jumpforce;
		Ogre::Vector3 tOvrBck = overBlock();
		if(tOvrBck.y == 1)
		{int breaker = 0;}
		tOvrBck = overBlock();
		float t1 = vect32BlockID(tOvrBck);
		float t = r_Map[t1].getTop();
		if (pos.y < t + (dimentions.y / 2))
		{ pos.y = t + (dimentions.y / 2); jumping = false;}
	}
	speed += acceleration;
	velocity = getDirection() * speed;
	pos += velocity;
	mNode->setPosition(pos.x, pos.y, pos.z);


	//add the speed modifier from the block to the players current velocity
	//reasign the direction.
	//check the key and mouse inputs
	//assign new roll
	// check roll against the optimum roll
	//reasign speed
}
void Player::setJump()
{
	if (jumping == false){
		jumping = true;
		jumpforce = 0.3;
	}
}
Ogre::Vector3 Player::overBlock(){
	Ogre::Vector3 retVect = getBlock();
	int x, y, z;
	x = static_cast<int>(retVect.x);
	y = static_cast<int>(retVect.y) - 1;
	z = static_cast<int>(retVect.z);
	if ( y < 0){y++;}

	int blockNum = (z * 100) + (y * 10) + x;
	for(;r_Map[blockNum].blockType == Block::Block_Type::null;)
	{//return the first block under the player that isn't empty
		//Block::Block_Type tempBT = r_Map[blockNum].blockType;
		y--;
		blockNum = (z * 100) + (y * 10) + x;

	}
	retVect = Ogre::Vector3((float)x, (float)y, (float)z);

	return retVect;
}
int Player::vect32BlockID(Ogre::Vector3 vect3In){
	return ((vect3In.z * 100) + (vect3In.y * 10) + (vect3In.x));
}