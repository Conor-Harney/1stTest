#include "Player.h"

Player::Player(Ogre::Vector3 posIn, Ogre::SceneManager *sceneMan, vector<Block> & mapIn, float sizeIn): 
	mSceneMgr(sceneMan) ,score(0), deaths(0), velocity(Ogre::Vector3(0,0,0)), 
		acceleration(Ogre::Vector3(0,0,0)), m_position(posIn), jumping(false), r_Map(mapIn), m_speed(0.5), 
		dimentions(Ogre::Vector3(sizeIn, sizeIn, sizeIn)), m_isSideJumping(false), m_fallenOff(false), m_mass(1)
{
	mEntity = mSceneMgr->createEntity("Player", "daily_grind_player.mesh");// "Cube.mesh");//daily_grind_player.mesh
	//mEntity->setMaterialName("Examples/BumpyMetal");
    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->setPosition(posIn);
	float modelSize = 4; //200;
	mNode->scale(sizeIn / 4, sizeIn / 4, sizeIn / 4);
	//mNode->yaw(Ogre::Radian(3.14159f), Ogre::Node::TransformSpace(0));
	mNode->roll(Ogre::Radian(Ogre::Math::HALF_PI), mNode->TS_LOCAL);
	leanBack = false;
}
 


Ogre::Vector3 Player::getBlock(){
	Ogre::Vector3 blockIn;
	blockIn = Ogre::Vector3(m_position.x / Block::size, m_position.y / Block::size, m_position.z / Block::size);
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
	if(m_position.z >50){
			int breaker = 1;
		}
	retSpeed = r_Map[vectBlockNum].getSpeedMod();
	}

	return retSpeed;
}

Ogre::Vector3 Player::getDirection(){
	Ogre::Vector3 retDirect = Ogre::Vector3(0,0,1);

	if(getBlock().y > 0){
		Ogre::Vector3 tempBlockOn = overBlock();
		int vectBlockNum = ((tempBlockOn.x * 100) + (tempBlockOn.y * 10) + tempBlockOn.z);
		retDirect = r_Map[vectBlockNum].getDirection();
	}
	
	return retDirect;
}

float Player::getOptimumRoll(){
	return 0.0f;
}

void Player::update(double timePassed){
	
	//m_position.x += 0.001;
	
	//acceleration = getSpeedMod();

	if (jumping == true)
	{ 
		acceleration.y -= 9.81 * timePassed;
		m_position.y += acceleration.y;
		Ogre::Vector3 tOvrBck = overBlock();
		tOvrBck = overBlock();
		float t1 = vect32BlockID(tOvrBck);
		float t = r_Map[t1].getTop();
		if (m_position.y < t + (dimentions.y / 2) - 1)
		{	m_position.y = t + (dimentions.y / 2); jumping = false; acceleration.y = 0;}
	}
	m_speed += getSpeedMod();
	velocity.x = getDirection().x * m_speed;
	velocity.z = getDirection().z * m_speed;
	m_position.x += velocity.x;
	m_position.z += velocity.z;
	if(jumping == false){
		if(getDirection().x == 0){
			float sub = std::fmod(m_position.x, 25);
			if (sub > 13.5)
			{ sub = sub - 25;}
			m_position.x = int(m_position.x - sub);
		}
		else if(getDirection().z == 0){
			float sub = std::fmod(m_position.z, 25);
			if (sub > 13.5)
			{ sub = sub - 25;}
			m_position.z = int(m_position.z - sub);
		}
	}
	mNode->setPosition(m_position.x, m_position.y, m_position.z);
	//lean();
	//if (leanBack)
	//{
	//	stopLean();
	//}

	if(m_isSideJumping == true){changeRail(timePassed);}
	Ogre::Vector3 lkAtVec = m_position + getDirection();
	mNode->lookAt(lkAtVec, Ogre::Node::TS_WORLD, Ogre::Vector3(0,0,1));



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
		jumpforce = 4;
		acceleration.y += jumpforce / m_mass;
		//f = ma
		//a = f/m
		//acceleration 
	}
}
Ogre::Vector3 Player::overBlock(){
	Ogre::Vector3 retVect = getBlock();
	int x, y, z;
	x = static_cast<int>(retVect.x);
	y = static_cast<int>(retVect.y) - 1;
	z = static_cast<int>(retVect.z);
	//if ( y < 0)
	//{y++;}

	int blockNum = (z * 100) + (y * 10) + x;
	for(;r_Map[blockNum].blockType == Block::Block_Type::null;)
	{//return the first block under the player that isn't empty
		//Block::Block_Type tempBT = r_Map[blockNum].blockType;
		if(y == 0){
			m_fallenOff = true;
			break;
		}
		y--;
		blockNum = (z * 100) + (y * 10) + x;

	}
	retVect = Ogre::Vector3((float)x, (float)y, (float)z);
	return retVect;
}
int Player::vect32BlockID(Ogre::Vector3 vect3In){
	return ((vect3In.z * 100) + (vect3In.y * 10) + (vect3In.x));
}
int Player::blockOverId(){
	return vect32BlockID(overBlock());
}

void Player::setLean(std::string direction){
	if(direction == "->"){
		m_Angle = Ogre::Radian(0.02);
	}
	else if (direction == "<-"){
		m_Angle = -(Ogre::Radian(0.02));
	}
	
}

Ogre::Quaternion Player::getOrientation(){
	return mNode->getOrientation();
}

void Player::lean(){
	//Ogre::Vector3 v = Ogre::Vector3(0,dimentions.y,0);
	//Ogre::Matrix3 R;
	//R.FromEulerAnglesXYZ(Ogre::Degree(0),Ogre::Degree(0),Ogre::Degree(m_Angle));
	//mNode->translate(v);
	//mNode->rotate(R);
	//mNode->translate(-v);
}

void Player::stopLean(){
	/*leanBack = true;
	Ogre::Matrix3 R;
	Ogre::Vector3 V3R = getDirection() * 90;
	R.FromEulerAnglesXYZ(Ogre::Degree(V3R.x),Ogre::Degree(V3R.y),Ogre::Degree(V3R.z));
	m_Angle = 0.0;
	if(mNode->getOrientation() != R){

		if(mNode->getOrientation().getRoll < Ogre::Radian(Ogre::Math::HALF_PI - 0.1)){
			m_Angle = (Ogre::Radian(0.02));
		}
		else{
			leanBack = false;
			mNode->setOrientation(R);
			m_Angle = 0.0;
		}
	}*/
}
Ogre::Vector3 Player::GetPosition()
{
	return m_position;
}

void Player::sideJump(std::string jumpWhere){
	if(m_isSideJumping == false && (jumpWhere == "LEFT" || jumpWhere == "RIGHT")){
		m_isSideJumping = true;
		m_AmountToSideJump = Block::size;
		m_JumpPerSecond = m_AmountToSideJump * 1.5;
		Ogre::Vector3 travlingIn = getDirection();
		if(jumpWhere == "LEFT"){
			m_jumpingIn.x = travlingIn.z;
			m_jumpingIn.z = -travlingIn.x;
		}
		else if(jumpWhere == "RIGHT")
		{
			m_jumpingIn.x = -travlingIn.z;
			m_jumpingIn.z = travlingIn.x;
		}
		else{
			bool breaker = true;
		}
		m_jumpingIn.y = 0;
	}
}
void Player::changeRail(float timePassed){
	float sideJumpAmount = m_JumpPerSecond * timePassed;
	if(m_AmountToSideJump - sideJumpAmount < 0){
		sideJumpAmount += m_AmountToSideJump - sideJumpAmount;
	}

	m_position += m_jumpingIn * sideJumpAmount;
	m_AmountToSideJump -= sideJumpAmount;
	if(m_AmountToSideJump <= 0){m_isSideJumping = false;}
}

void Player::setPosition(Ogre::Vector3 posIn){
	m_position = posIn;
}