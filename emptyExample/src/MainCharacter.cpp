#include "MainCharacter.h"
#include "TerrainVertex.h"

void MainCharacter::setup()
{
	
	//	aLoader.load(ofToDataPath("3DAssets/vrouwAnimeTest2.dae"));
aLoader.load(ofToDataPath("3DAssets/girlStop.dae"));
aLoader.addAnimation(ofToDataPath("3DAssets/girlWalk.dae"));

	charMesh  = *aLoader.boneMeshes[0];
	charMesh.setPos(0,0,0);
	charMesh.material.loadDiffuse("3DAssets/vrouwFinal.png");
	walkDirRot =0;
	rotSpeed =2;
	//walkDir.set(-0.085,0,0.996);
	//charPos.set(98.99,77.23,189.178);

		walkDir.set(-0.085,0,0.996);
	charPos.set(0,0,0);

	walkspeed =15/3;
	 isMoving =false;
	 lastDown =-1;
	 rightIsDown =false;
	 leftIsDown =false;
	  walkSlerp=0;
}
void MainCharacter::update(unsigned long timeStep)
{
	
	
	
	charMesh.update((float)timeStep/300000 ,walkSlerp,0,1);

	if (lastDown >-1)
	{
	
		if (lastDown==RIGHT_DOWN)
		{
		walkDirRot-= rotSpeed * (float)timeStep/1000000;
		
		}else
		{
		walkDirRot+= rotSpeed * (float)timeStep/1000000;
		
		}
	
	
		walkDir.set(sin(walkDirRot),0,cos (walkDirRot));
		if (!isMoving){walkSlerp =0.4;}

		walkDir.normalize();
	
	}


	if (isMoving){
	charPos  +=walkDir*(walkspeed* (float)timeStep/1000000);

	walkSlerp +=0.2;
	if (walkSlerp>1)walkSlerp =1;
	}else
	{
	walkSlerp -=0.2;
	if (walkSlerp<0)walkSlerp =0;
	}
	if (chunkHandler->frameCount>10){
	TerrainVertex v = chunkHandler->getVertexforPos(charPos);
	
	charPos.y =v.position.y;//+2.3;
	//charPos.x =v.position.x; 
	//charPos.z =v.position.z;//  terrainFunctions->getHeightForPos(charPos.x, charPos.z) +2.3;
	}
	charMesh.objectMatrix.makeLookAtViewMatrix(ofVec3f(0,0,0),walkDir,ofVec3f(0,-1,0));
	charMesh.objectMatrix.postMultTranslate(charPos);
	//	charMesh.objectMatrix.preMultScale(ofVec3f(5,5,5));
	charMesh.calculateNormalMatrix();
	//cout <<charPos <<" " <<walkDir<< endl;
}


void  MainCharacter::setKey(int key)
{

if (key== FORWARD_DOWN) isMoving =true;
else if (key== FORWARD_UP) isMoving =false;
	
else if (key== RIGHT_DOWN)
{
	lastDown= RIGHT_DOWN;
	
	rightIsDown =true;
} 
else if (key== LEFT_DOWN)
{
	lastDown= LEFT_DOWN;
	
	leftIsDown =true;
} else if (key== RIGHT_UP)
{
	rightIsDown =false;
	if (leftIsDown)
	{
		lastDown  =  LEFT_DOWN;
	}else
	{
		lastDown =-1;
	}
} 
else if (key== LEFT_UP)
{
	leftIsDown =false;
	if (rightIsDown)
	{
		lastDown  = RIGHT_DOWN;
	}else
	{
		lastDown =-1;
	}
} 



}