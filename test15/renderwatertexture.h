//
//  testsay.h
//  OpenGLExample
//
//  Created by chenbo on 9/28/16.
//  Copyright (c) 2016 chenbo. All rights reserved.
//

#ifndef __OpenGLExample__testsay__
#define __OpenGLExample__testsay__

#include <stdio.h>

#include "GL/glus.h"

typedef struct _WaveParameters
{
    GLfloat speed;
    GLfloat amplitude;
    GLfloat wavelength;
    GLfloat steepness;
} WaveParameters;

typedef struct _WaveDirections
{
    GLfloat x;
    GLfloat z;
} WaveDirections;

GLUSuint initWaterTexture(GLUSfloat waterPlaneLength);

GLUSvoid reshapeWaterTexture(GLUSint width, GLUSint height);

GLUSboolean renderWaterTexture(GLUSfloat time);

GLUSvoid terminateWaterTexture(GLUSvoid);


#endif /* defined(__OpenGLExample__testsay__) */
