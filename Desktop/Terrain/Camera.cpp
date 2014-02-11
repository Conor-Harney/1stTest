#include "stdafx.h"
#include "Camera.h"
#include "SFML/OpenGL.hpp" 

    void Camera::MoveLeftRight(int dir)
	{ //Dir=+1=>Right, dir=-1=> Left
		aiVector3D sideWays = forward^up;
		sideWays *= dir;
        position+=sideWays;
    }
 
    void Camera::MoveForwardBack(int dir)
	{ //Dir=+1=>Forward, dir=-1=> Back 
        position+=(forward*(forwardSpeed*dir));
    }
 
    void Camera::TurnRightLeft(int dir)
	{ //Dir=+1=>Right, dir=-1=> Left
      
		float angle = roationSpeed* -dir;
		m.Rotation(angle,up,m);
		forward *= m;
		forward.Normalize();
    }
         
    void Camera::TurnUpDown(int dir)
	{ //Dir=+1=>Up, dir=-1=> Down
		float angle = roationSpeed* dir;
		m.Rotation(angle,forward^up,m);
		forward *= m;
		up *= m;
		forward.Normalize();
		up.Normalize();
    }
 
    void Camera::ViewingTransform()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(	position.x,position.y,position.z,// camera position
					position.x+forward.x,position.y+forward.y,position.z+forward.z, //look at this point
					0,1,1); //camera up
    }
 

aiVector3D Camera::zero(0.0f);
aiVector3D Camera::yaxis(0.0f,1.0f,0.0f);
aiVector3D Camera::zaxis(0.0f,0.0f,1.0f);