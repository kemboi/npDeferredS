#include "testApp.h"
#include "GLErrorCheck.h"

//--------------------------------------------------------------
void testApp::setup(){

	/*int units;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,  &units);
	cout <<"maxTexture units " <<units<< endl;

	*/
	ofSetFrameRate(60);
    
	srand(3);
	chunkHandler.setup();
	
	terain.chunkHandler = &chunkHandler;
	terain.setup(ofToDataPath("3DAssets/Terain.png"),ofToDataPath("3DAssets/objects.png"));

	girl.setup();
	girl.terain =  &terain;

	camera.setup();
	camera.mainCharacter =&girl;
	camera.terrain =   &terain;
	ofBackground(0, 0, 0);
    /*
    npMaterial m;
    m.hasColor =true;
    m.hasUV =false;
    m.r =0.9f;
    m.g =0.9f;
    m.b =0.9f;*/
    /*for (int i=0;i<80;i++)
    {
        npSphere *t =new npSphere();
        t->setup(m,(float) rand()/RAND_MAX*1.0+0.5);
        t->setPos (((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20);
        spheres.push_back((npMesh *)t);
    
    }*/
    for (int i=0;i<40;i++)
    {
    
        npPointLight *p = new npPointLight();
        
		if (i==0)
		{
		
		p->setup(20,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX ,(float) rand()/RAND_MAX ,1);
		}
		else
		{
		
		p->setup(5,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX ,(float) rand()/RAND_MAX ,0.2f);
		}
	



      p->setPos (((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20);
         //p->setPos (0,0,0);
        pLights.push_back(p );
    
    
    }
    
  
		
  
    
	boneMeshRenderer.setup();

    rendererColor.setup();

	renderTexture.setup();
	
	terrainRenderer.setup();

	
    deferredBuffer.setup(ofGetScreenWidth(),ofGetScreenHeight());
    
  
    plRenderer.setup(ofGetScreenWidth(),ofGetScreenHeight());
    plRenderer.depthTexture =deferredBuffer.depthTexture;
    plRenderer.normalTexture=deferredBuffer.normalTexture;
    
    
    
    deferredFinal.depthTexture =deferredBuffer.depthTexture;
    deferredFinal.normalTexture =deferredBuffer.normalTexture;
    deferredFinal.colorTexture =deferredBuffer.colorTexture;
    deferredFinal.pointLightTexture = plRenderer.pointLightTexture;
    deferredFinal.setup("DeferredShaderFinal");
    
 
   
	dirLight.lookAt.set(0,0,0);
	dirLight.pos.set(750,750,0);

	deferredFinal.dirLight =&dirLight;
	

	shadowMap.setup();
	deferredFinal.shadowTexture1 =shadowMap.shadowTexture1;
	shadowMeshRenderer.setup();
	shadowBoneRenderer.setup();
	previousTime=ofGetElapsedTimeMicros();
	currentTime =ofGetElapsedTimeMicros();


	GLErrorCheck::test("setup end");
	cout << "setupDone"<< endl;
}



//--------------------------------------------------------------
void testApp::update(){
	
	currentTime =ofGetElapsedTimeMicros();
	 timeStep =currentTime -previousTime;   
	previousTime  = currentTime;
	
	float cycleTime =  (currentTime/1000)%60000;
	dayTime = cycleTime/60000 ;



	//
	// PRE RENDER UPDATE
	//
	//
	girl.update(timeStep);
	dirLight.update();

	camera.lightDir = dirLight.dir;
	camera.setMouse(mouseIsDown,vecMouseMove.x,vecMouseMove.y);
	camera.update();
	chunkHandler.update(camera.lookAtPos,camera.camPos);
	
	//
	//
	// FRAME  BUFFERS
	//
	//
	
	//
    // SHADOW MAP DRAW;
	//
	glPolygonOffset(4.2,1.2);
	glEnable(GL_POLYGON_OFFSET_FILL);
	shadowMap.start();
	glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_LESS,0.5f);
		shadowMeshRenderer.start(camera);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel==1)
				{
			
			
					shadowMeshRenderer.draw( chunkHandler.chunks[i]->terrainHighRes);
					for (int j=0;j< chunkHandler.chunks[i]->objects.size();j++)
					{
				
					
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->objects[j]);
					}
			
				 }
				 
		}
		shadowMeshRenderer.stop();
			glDisable(GL_ALPHA_TEST);
		shadowBoneRenderer.start(camera);
		shadowBoneRenderer.draw(&girl.charMesh);
		shadowBoneRenderer.stop();

	shadowMap.stop();
	glViewport(0,0 , 1920,1080);
	glDisable(GL_POLYGON_OFFSET_FILL);
	//
    // MAIN DRAW;
	//
    glEnable(GL_DEPTH_TEST);
  //  glEnable(GL_CULL_FACE);
	glClearColor(0.8f,0.8f,1.0f,1.0f);
    deferredBuffer.start();
		// terain floor
		terrainRenderer.start(camera);
			for (int i=0;i< chunkHandler.chunks.size();i++)
				{
				if (chunkHandler.chunks[i]->detailLevel==2)
				{
					terrainRenderer.draw( chunkHandler.chunks[i]->terrainLowRes);
				}
				else if(chunkHandler.chunks[i]->detailLevel==1)
				{
					terrainRenderer.draw( chunkHandler.chunks[i]->terrainHighRes);
				
				}
		}
		terrainRenderer.stop();
		glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER,0.5f);

		renderTexture.start(camera);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel>0)
				{
				
					for (int j=0;j< chunkHandler.chunks[i]->objects.size();j++)
					{
				
					
						renderTexture.draw(	chunkHandler.chunks[i]->objects[j]);
					}
				 }
			}
		renderTexture.stop();
			glDisable(GL_ALPHA_TEST);
	/*	rendererColor.start(camera);
	
		

	for (int i=0;i< chunkHandler.chunks.size();i++)
		{
				 if(chunkHandler.chunks[i]->detailLevel>0)
				{
				
					for (int j=0;j< chunkHandler.chunks[i]->objects.size();j++)
					{
					
						rendererColor.draw(chunkHandler.chunks[i]->objects[j]);
					}
				 }
	
		}
		rendererColor.stop();
		*/
		boneMeshRenderer.start(camera);
			boneMeshRenderer.draw(&girl.charMesh);
		boneMeshRenderer.stop();
    deferredBuffer.stop();
 
   
	//
    // POINTLIGHT DRAW;
	//
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
	glCullFace(GL_FRONT);
	plRenderer.draw(pLights ,camera);
	glCullFace(GL_BACK);
    glDisable (GL_BLEND);
    
	
	GLErrorCheck::test("update end");
   
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
   deferredFinal.draw(&camera,  dayTime);

   GLErrorCheck::test("draw end");
// cout << ofGetFrameRate()<<endl ;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	switch (key) {
		case OF_KEY_UP: 
			girl.setKey(MainCharacter::FORWARD_DOWN);
		
        break;
		case OF_KEY_LEFT: 
		
		girl.setKey(MainCharacter::LEFT_DOWN);
        break;
		case OF_KEY_RIGHT: 
			girl.setKey(MainCharacter::RIGHT_DOWN);
		
        break;
    }
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	switch (key) {
	case OF_KEY_UP: 

			girl.setKey(MainCharacter::FORWARD_UP);
        break;
		case OF_KEY_LEFT: 
		girl.setKey(MainCharacter::LEFT_UP);
        break;
		case OF_KEY_RIGHT: 
			girl.setKey(MainCharacter::RIGHT_UP);
		
          break;
     
        }
          
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
		
		if ( button ==0)
		{
			vecMouseMove.set(x -vecMouseStart.x,y -vecMouseStart.y);
		}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	if ( button ==0)
	{
		vecMouseStart.set(x,y);
		mouseIsDown = true;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if ( button ==0)
	{
		mouseIsDown = false;
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
