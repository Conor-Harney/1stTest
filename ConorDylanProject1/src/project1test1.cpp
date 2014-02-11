

#include "project1test1.h"

//-------------------------------------------------------------------------------------
project1test1::project1test1(void)
{
}
//-------------------------------------------------------------------------------------
project1test1::~project1test1(void)
{
	delete player1;
}


//-------------------------------------------------------------------------------------
void project1test1::createScene(void)
{
	m_preppedJumpDir = "";
	mute = false;
	tempCounter = 0;
	mBlockVector.reserve(1000);
	float blockSize = 50;
	Ogre::Vector3 blockDirection = Ogre::Vector3(0,0,1);
	std::ofstream myfile;
	myfile.open ("mapFile.txt");
	
	for(int ix = 0; ix < 10; ix++)	{
		for(int iy = 0; iy < 10; iy++)	{
			for(int iz = 0; iz < 10; iz++){
				blockDirection = Ogre::Vector3(0,0,1);
					 if (ix == 0 || (ix == 1 && iz != 9 && iz != 0)){blockDirection = Ogre::Vector3(0,0,1);}
				else if (iz == 9 || (iz == 8 && ix != 0 && ix != 9)){blockDirection = Ogre::Vector3(1,0,0);}
				else if (ix == 9 || (ix == 8 && iz != 9 && iz != 0)){blockDirection = Ogre::Vector3(0,0,-1);}
				else if (iz == 0 || (iz == 1 && ix != 0 && ix != 9)){blockDirection = Ogre::Vector3(-1,0,0);}
				//corners
					 if((ix == 0 && iz == 9) || (ix == 1 && iz == 8))	{blockDirection = Ogre::Vector3(0.5,0,0.5);}
				else if((ix == 9 && iz == 9) || (ix == 8 && iz == 8))	{blockDirection = Ogre::Vector3(0.5,0,-0.5);}
				else if((ix == 9 && iz == 0) || (ix == 8 && iz == 1))	{blockDirection = Ogre::Vector3(-0.5,0,-0.5);}
				else if((ix == 0 && iz == 0) || (ix == 1 && iz == 1))	{blockDirection = Ogre::Vector3(-0.5,0,0.5);}

				mBlockVector.push_back( Block(Ogre::Vector3(ix, iy, iz), Ogre::Vector3((ix * blockSize) + (blockSize / 2), (iy * blockSize) + (blockSize / 2), (iz * blockSize) + (blockSize / 2)), blockDirection ));
				Block::Block_Type BT1 = Block::Block_Type::null;
				if(iy == 0){
					if(ix == 0 || ix == 1 || ix == 9 || ix == 8 || iz == 0 || iz == 1 || iz == 9 || iz == 8){
						BT1 = Block::Block_Type::streightRaill;
						if((ix == 0 && iz == 0) || (ix == 1 && iz == 1) || (ix == 9 && iz == 0) || (ix == 8 && iz == 1) || (ix == 0 && iz == 9) || (ix == 1 && iz == 8) || (ix == 9 && iz == 9) || (ix == 8 && iz == 8) ){
							BT1 = Block::Block_Type::curvedRail;
						}
					}
				}
				mBlockVector[mBlockVector.size() - 1].initilise(mSceneMgr, BT1);
				myfile << ix << ","<< iy << ","<< iz << "," << (ix * blockSize) + (blockSize / 2) << "," << (iy * blockSize) + (blockSize / 2) << "," << (iz * blockSize) + (blockSize / 2) << "," << blockDirection.x << "," << blockDirection.y << "," << blockDirection.z << "," << BT1;

			}
		}
	}
	myfile.close();
	float playerSize = 50.0f;
	player1 = new Player(Ogre::Vector3(blockSize/ 2 , mBlockVector[0].getTop() + (playerSize * 0.5), (blockSize / 2) * 3), mSceneMgr, mBlockVector, playerSize);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);


	
	Ogre::Vector3 obPos = Ogre::Vector3(20,60,300);
	obstacleNode = new Ogre::SceneNode(mSceneMgr, "obstacleNode");
	obstacleEntity = mSceneMgr->createEntity("Obstacle", "Cube.mesh");
	obstacleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	obstacleNode->attachObject(obstacleEntity);
	obstacleNode->setPosition(Ogre::Vector3(obPos));
	obstacleNode->scale(0.5,0.2,0.1);
	mObstacle = new Obstacle(obstacleNode, Ogre::Vector3(obPos), 50, 20, 10);
	
	

	std::string soundFileLoc[NUMOFSOUNDS];
	int stringCounter = 0;
	soundFileLoc[stringCounter] = "C://Program Files (x86)//FMOD SoundSystem//FMOD Programmers API Windows//examples//media//projectMusic.mp3";
	stringCounter++;
	soundFileLoc[stringCounter] = "C://Program Files (x86)//FMOD SoundSystem//FMOD Programmers API Windows//examples//media//Jump.wav";
	stringCounter++;
	soundFileLoc[stringCounter] = "C://Program Files (x86)//FMOD SoundSystem//FMOD Programmers API Windows//examples//media//Pop(2).WAV";
	stringCounter++;
	soundFileLoc[stringCounter] = "C://Program Files (x86)//FMOD SoundSystem//FMOD Programmers API Windows//examples//media//beeping.mp3";
	stringCounter++;
	if (stringCounter != NUMOFSOUNDS)
	{
		std::cout << "sound location not set error! (%d) %s\n";
		exit(-1);
	}

		result = FMOD::System_Create(&FMODsys);
     // Create the main system object.
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s\n" <<result;// << FMOD_ErrorString(result);
			exit(-1);
		}		result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
     
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
			exit(-1);
		}	
		
		result = FMODsys->createStream(soundFileLoc[0].c_str(), FMOD_3D, 0, &sounds[0]);

	for(int i = 1; i < NUMOFSOUNDS; i++){
	//setup FMOD
		if(i != 3){
			result = FMODsys->createSound(soundFileLoc[i].c_str(), FMOD_3D, 0, &sounds[i]);}
		else{result = FMODsys->createSound(soundFileLoc[i].c_str(), FMOD_LOOP_NORMAL|FMOD_3D, 0, &sounds[i]);}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float volume=1.9f;
	FMODsys->playSound(FMOD_CHANNEL_FREE, sounds[3], false, &channels[3]);
	result = channels[3]->setVolume(volume);    
	//need this for sound fall off
	channels[3]->set3DMinMaxDistance(150,500);
	FMOD_REVERB_PROPERTIES prop1 = FMOD_PRESET_CAVE;
	FMODsys->setReverbAmbientProperties(&prop1);

	//
	FMOD_REVERB_PROPERTIES myReverbProp = {  
    0,  22, 1.00f, //diffusion
    -0,  0,  0.5,  //room effect (med,low, high freq)
    1.49f,  0.10f, 1.0f, //decay  
    -449, 0.30f,//reflections  
    -5700, 0.011f, //reverb
    1.18f, 0.348f, //modulation
    5000.0f, 250.0f, //reference
    100.0f, 200.0f, //echo density
    0x3f };
	 
	FMOD::Reverb *reverb;
	result = FMODsys->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	reverb->setProperties(&prop);
	Ogre::Vector3 reverbPos = Ogre::Vector3(0,0,0);
	FMOD_VECTOR pos = {reverbPos.x, reverbPos.y, reverbPos.z };
	float mindist = 100.0f; 
	float maxdist = 150.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);
	 
	reverb->setActive(true);
	
	FModManager::System()->playSound(FMOD_CHANNEL_FREE, sounds[0], false, &channels[0]);
	InitialiseParticles();
}

bool project1test1::keyPressed( const OIS::KeyEvent &arg ){
	
	if (arg.key == OIS::KC_SPACE)   // toggle visibility of advanced frame stats
    {

		
		if (player1->jumping == false){
			tempCounter++;
			player1->setJump();
			if(m_preppedJumpDir != ""){
				player1->sideJump(m_preppedJumpDir);
			}
			if(mute == false){
				FModManager::System()->playSound(FMOD_CHANNEL_FREE, sounds[1], true, &channels[1]);
				channels[1]->setVolume(1.0f);
				channels[1]->setPaused(FALSE);
			}
		}

    }
	if (arg.key == OIS::KC_LEFT)
	{
		m_preppedJumpDir = "LEFT";
	}
	else if (arg.key == OIS::KC_RIGHT)
	{
 		m_preppedJumpDir = "RIGHT";
	}
	if (arg.key == OIS::KC_M)
    {
		switchMute();
	}
	if (arg.key == OIS::KC_NUMPAD0)
    {

		bool* ptr_pause = new bool();
		channels[0]->getPaused(ptr_pause);

		if(*ptr_pause == true){ptr_pause = false;}
		else{*ptr_pause = true;}

		channels[0]->setPaused(ptr_pause);


	}
	if (arg.key == OIS::KC_NUMPAD1)
    {
		bool* ptr_pause = new bool();
		channels[1]->getPaused(ptr_pause);
		if(*ptr_pause == true){ptr_pause = false;}
		else{*ptr_pause = true;}
		channels[1]->setPaused(ptr_pause);
	}
	if (arg.key == OIS::KC_NUMPAD2)
    {
		bool* ptr_pause = new bool();
		channels[2]->getPaused(ptr_pause);
		if(*ptr_pause == true){ptr_pause = false;}
		else{*ptr_pause = true;}
		channels[2]->setPaused(ptr_pause);
	}
	if (arg.key == OIS::KC_NUMPAD3)
    {
		bool* ptr_pause = new bool();
		channels[3]->getPaused(ptr_pause);
		if(*ptr_pause == true){ptr_pause = false;}
		else{*ptr_pause = true;}
		channels[3]->setPaused(ptr_pause);
	}


	if (arg.key == OIS::KC_Q)
    {
		player1->setLean(std::string("->"));
	}
	if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
	
	
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    mCameraMan->injectKeyDown(arg);

	return true;
}

bool project1test1::keyReleased( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyUp(arg);
	if(arg.key == OIS::KC_Q){
		player1->stopLean();
	}
	if (arg.key == OIS::KC_LEFT && player1->jumping == true)
	{
		if(m_preppedJumpDir == "LEFT"){
			m_preppedJumpDir = "";
		}
	}
	else if (arg.key == OIS::KC_RIGHT && player1->jumping == true)
	{
		if(m_preppedJumpDir == "RIGHT"){
			m_preppedJumpDir = "";
		}
	}
    return true;
}

bool project1test1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	double timePassed = evt.timeSinceLastFrame;
	player1->update(timePassed);
	UpdateCamera();

	Ogre::Vector3 playerPos = player1->GetPosition();
	Ogre::Vector3 playerDir = player1->getDirection();

	for(int i = 0; i < 50; i++)
	{
		m_particles[i].update();

		if(m_particles[i].GetLifeLeft()<0&& player1->jumping==false)
		{
			m_particles[i].reset(playerPos, playerDir);
			//m_lifeSpan = 100;

			if(i%2==0)
			{
				m_particles[i].setVelocity();
			}
		}
	}

	
	if(mObstacle->IsHit(player1->GetPosition(), player1->dimentions.x, player1->dimentions.y, player1->dimentions.z))
	{
  		obstacleNode->setVisible(false);
		FModManager::System()->playSound(FMOD_CHANNEL_FREE, sounds[2], false, &channels[2]);
	}
	

	Ogre::Vector3 lVelocity = player1->velocity;
	FMOD_VECTOR  listenervel  = { lVelocity.x, lVelocity.y, lVelocity.z };
	FMOD_VECTOR  listenerpos  = { player1->GetPosition().x, player1->GetPosition().y, player1->GetPosition().z };
	const FMOD_VECTOR  listenerForward  = { player1->getDirection().x, player1->getDirection().y, player1->getDirection().z };
	//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
	FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, &listenerForward, 0);
         
	//update position of sound
	//for (int i = 0; i < OBSTACLENUM; i++){
		FMOD_VECTOR  sourcePos  = { mObstacle->getPosition().x , mObstacle->getPosition().y, mObstacle->getPosition().z };
		
		//source is fixed so velocity is zero
		channels[3]->set3DAttributes(&sourcePos,0);
	//}

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
			float ovBY = player1->overBlock().y; 
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(player1->overBlock().x));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(player1->overBlock().y));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(player1->overBlock().z));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(player1->GetPosition().x));
			mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(player1->GetPosition().y));
			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(player1->GetPosition().z));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(player1->jumping));
        }
    }
	


	FMODsys->update();

    return true;
}

void project1test1::switchMute(){
	if(mute == false){
		mute = true;
		for(int i = 0; i < NUMOFCHAN; i++){
			channels[i]->stop();
		}
	}
	else{
		mute = false;
		FModManager::System()->playSound(FMOD_CHANNEL_FREE, sounds[0], false, &channels[0]);
	}
}

void project1test1::UpdateCamera()
{
	//CAMERA ORIENTATION
	Ogre::Vector3 playerPos = player1->GetPosition();
	if(player1->jumping == false){
		Ogre::Vector3 playerDir = player1->getDirection();

		playerDir*=-150;

		m_camPos = playerPos+playerDir;
		m_camPos.y += 50;
	}

	mCamera->setPosition(m_camPos);

    mCamera->lookAt(playerPos);
}


void project1test1::InitialiseParticles()
{
	for(int i = 0; i < 50; i++)
	{
		Ogre::String my_string = Ogre::StringConverter::toString(i);
		Ogre::Entity *sphere2 = mSceneMgr->createEntity("sphere"+my_string, "sphere.mesh");

		sphere2->setMaterialName("Examples/Hilite/Yellow");

		Ogre::SceneNode *sphereNode2 = mSceneMgr->createSceneNode("sphereNode"+my_string);

		mSceneMgr->getRootSceneNode()->addChild(sphereNode2);

		sphereNode2->attachObject(sphere2);

		sphere2->setCastShadows(true);

		double sphModelRadius = 50;

		double sphModelHeight = 100;

		double sphRadius = 0.15;

		double sphHeight = 0.3;

		sphereNode2->scale(sphRadius/sphModelRadius, sphHeight/sphModelHeight, sphRadius/sphModelRadius);

		sphereNode2->setPosition(player1->GetPosition());

		//iSecret = rand() % 10 + 1;
		float xVel = (rand() % 10 + 1)/1;
		float yVel = (rand() % 10 + 1)/1;
		float zVel = (rand() % 10 + 1)/1;

		xVel /= 100;
		yVel /= 100;
		zVel /= 100;

		m_particles[i].init(sphereNode2, .30, player1->GetPosition(), player1->getDirection());
	}
}





#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        project1test1 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
