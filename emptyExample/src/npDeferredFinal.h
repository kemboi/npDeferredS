//
//  npFullscreenTexture.h
//  polygonExample
//
//  Copyright (C) 2011 Kris Temmerman,  www.neuroproductions.be
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
//  is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef polygonExample_npFullscreenTexture_h
#define polygonExample_npFullscreenTexture_h

#include "npIncludes.h"
#include "npDirectionalLight.h"
#include "npCamera.h"

class npDeferredFinal
{

public:
    npDeferredFinal(){};

    
    
    void setup(string prog ="DeferredShaderFinal");
    void draw(const npCamera &cam,float time,float colorFactor);

    float *dataFB;
	GLint uLightDir;
	GLint uWorldMatrix;
	GLint uWorldMatrixInv;
	GLint uPerspectiveInvMatrix;



	GLint uTime;
	GLint  uColorFactor;
	GLint uColorTexture;
    GLint uNormalTexture;
    GLint uDepthTexture;
    GLint uPointLightTexture;
	GLint uLambertMap;
	GLint uShadowTexture;


    GLuint depthTexture;
    GLuint colorTexture;	
    GLuint normalTexture;
    GLuint pointLightTexture;
    GLuint lambertMap;
	GLuint shadowTexture;


    GLuint program;
   
	npDirectionalLight * dirLight;
};

#endif
