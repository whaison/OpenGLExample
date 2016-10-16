//
//  wavefront.hpp
//  OpenGLExample
//
//  Created by chenbo on 16/10/2016.
//  Copyright © 2016 chenbo. All rights reserved.
//

#ifndef wavefront_hpp
#define wavefront_hpp


#include "GL/glus.h"

#define TEXTURE_WIDTH 640
#define TEXTURE_HEIGHT 480

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

#endif /* wavefront_hpp */
