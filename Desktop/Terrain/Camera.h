#ifndef Camera_H
#define Camera_H
#include <iostream>

#pragma comment(lib,"assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Camera
{
    static aiVector3D zero;
	static aiVector3D yaxis;
	static aiVector3D zaxis;
public:
    aiVector3D position;
    aiVector3D forward;
    aiVector3D up;
	aiMatrix3x3 m;
 
    float forwardSpeed;
    float roationSpeed;
     
    Camera():forwardSpeed(2.5f),roationSpeed(0.1f){}
 
    void Init(aiVector3D& p=zero, aiVector3D& f=zaxis, aiVector3D& u=yaxis)
	{
        position=p;
        forward=f;
        up=u;
	}

	void MoveLeftRight(int);
	void MoveForwardBack(int);
	void TurnRightLeft(int);
	void TurnUpDown(int);
	void ViewingTransform();
};

#endif