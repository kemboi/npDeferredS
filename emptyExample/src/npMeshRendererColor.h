//
//  npMeshRenderer.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npMeshRenderer_h
#define emptyExample_npMeshRenderer_h

#include "npIncludes.h"
#include "npMesh.h"
#include "npCamera.h"
#include "npMultiPointLight.h"
class npMeshRendererColor
{
public:
    npMeshRendererColor(){};
    ~npMeshRendererColor(){};
    
     
    
    void setup();
    
    
    void start(const npCamera &cam);
    void draw(const npMesh &mesh);
	   void draw(const npMultiPointLight &mpl);
	  void drawTriangle(const ofVec3f &p0,const ofVec3f &p1,const ofVec3f &p2);
    void stop();
    
   

    GLint program;
    GLint uNormalMatrix;
    GLint uNormalWorldMatrix;
    GLint uPerspectiveMatrix;
    GLint uWorldMatrix;
    GLint uObjectMatrix;
    
    
    enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_COLOR,
    };
    
};

#endif
