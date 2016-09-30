//
//  wavefront.h
//  OpenGLExample
//
//  Created by chenbo on 9/29/16.
//  Copyright (c) 2016 chenbo. All rights reserved.
//

#ifndef __OpenGLExample__wavefront__
#define __OpenGLExample__wavefront__


#include "GL/glus.h"

#define TEXTURE_WIDTH 800
#define TEXTURE_HEIGHT 600

/**
 * Properties of the camera.
 */
struct CameraProperties
{
    GLfloat eye[3];
    GLfloat center[3];
    GLfloat up[3];
};

/**
 * Properties of the light.
 */
struct LightProperties
{
    GLfloat direction[3];
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
};

/**
 * Properties of the material, basically all the color factors without the emissive color component.
 */
struct MaterialProperties
{
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
    GLfloat specularExponent;
};

/**
 * Locations for the light properties.
 */
struct LightLocations
{
    GLint directionLocation;
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
};

/**
 * Locations for the material properties.
 */
struct MaterialLocations
{
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
    GLint specularExponentLocation;
};

GLUSboolean initWavefront(GLUSfloat viewMatrix[16], struct LightProperties* light);

GLUSvoid reshapeWavefront(GLUSint width, GLUSint height);

GLUSboolean updateWavefront(GLUSfloat time, GLUSfloat scaleMatrix[16]);

GLUSvoid terminateWavefront(GLUSvoid);

#endif /* defined(__OpenGLExample__wavefront__) */
