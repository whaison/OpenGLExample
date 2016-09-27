
#include <stdio.h>

#include "GL/glus.h"

static GLUSprogram g_program;

static GLint g_modelViewProjectionMatrixLocation;

/**
 * The location of the normal matrix.
 */
static GLint g_normalMatrixLocation;

/**
 * The location of the light direction.
 */

/**
 * The location of the color.
 */

static GLint g_vertexLocation;

/**
 * The location of the texture coordinate in the shader program.
 */
static GLint g_texCoordLocation;

/**
 * The location of the normals.
 */
static GLint g_normalLocation;

static GLuint g_verticesVBO;

static GLuint g_texCoordsVBO;

/**
 * The VBO for the normals.
 */
static GLuint g_normalsVBO;

static GLuint g_indicesVBO;

static GLuint g_vao;

static GLuint g_numberIndicesCube;

/**
 * The texture.
 */
static GLuint g_texture;

GLUSboolean init(GLUSvoid)
{
    GLUStextfile vertexSource;
    GLUStextfile fragmentSource;
    
    GLUSshape cube;
    
    glusFileLoadText("shaders/Example04/shader/basic.vert.glsl", &vertexSource);
    glusFileLoadText("shaders/Example04/shader/color.frag.glsl", &fragmentSource);
    
    glusProgramBuildFromSource(&g_program, (const GLUSchar**) &vertexSource.text, 0, 0, 0, (const GLUSchar**) &fragmentSource.text);
    
    glusFileDestroyText(&vertexSource);
    glusFileDestroyText(&fragmentSource);
    
    //
    
    // Retrieve the uniform locations in the program.
    g_modelViewProjectionMatrixLocation = glGetUniformLocation(g_program.program, "u_modelViewProjectionMatrix");
    g_normalMatrixLocation = glGetUniformLocation(g_program.program, "u_normalMatrix");
    g_texCoordLocation = glGetAttribLocation(g_program.program, "a_texCoord");
    
    g_vertexLocation = glGetAttribLocation(g_program.program, "a_vertex");
    g_normalLocation = glGetAttribLocation(g_program.program, "a_normal");
    
    //
    
    // Use a helper function to create a cube.
    glusShapeCreateCubef(&cube, 0.5f);
    
    // Store the number indices, as we will render with glDrawElements.
    g_numberIndicesCube = cube.numberIndices;
    
    glGenBuffers(1, &g_verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.numberVertices * 4 * sizeof(GLfloat), (GLfloat*) cube.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &g_normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.numberVertices * 3 * sizeof(GLfloat), (GLfloat*) cube.normals, GL_STATIC_DRAW);
    
    glGenBuffers(1, &g_texCoordsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_texCoordsVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.numberVertices * 2 * sizeof(GLfloat), (GLfloat*) cube.texCoords, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Generate a VBO for the indices.
    glGenBuffers(1, &g_indicesVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.numberIndices * sizeof(GLuint), (GLuint*) cube.indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glusShapeDestroyf(&cube);
    
    //
    GLUStgaimage image;
    // Load the image.
    glusImageLoadTga("Binaries/desert.tga", &image);
    
    // Generate and bind a texture.
    glGenTextures(1, &g_texture);
    glBindTexture(GL_TEXTURE_2D, g_texture);
    
    // Transfer the image data from the CPU to the GPU.
    glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);
    
    // Setting the texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    //
    
    glUseProgram(g_program.program);
    
    glGenVertexArrays(1, &g_vao);
    glBindVertexArray(g_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, g_verticesVBO);
    glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(g_vertexLocation);
    
    glBindBuffer(GL_ARRAY_BUFFER, g_normalsVBO);
    glVertexAttribPointer(g_normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(g_normalLocation);
    
    glBindBuffer(GL_ARRAY_BUFFER, g_texCoordsVBO);
    glVertexAttribPointer(g_texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(g_texCoordLocation);
    
    // Also bind created texture ...
    glBindTexture(GL_TEXTURE_2D, g_texture);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesVBO);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // Setting default clear depth value.
    glClearDepth(1.0f);
    
    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
    
    // Enable back face culling.
    glEnable(GL_CULL_FACE);
    
    return GLUS_TRUE;
}

GLUSvoid reshape(GLUSint width, GLUSint height)
{
    GLfloat modelMatrix[16];
    GLfloat normalMatrix[9];
    GLfloat viewMatrix[16];
    GLfloat modelViewProjectionMatrix[16];
    
    glViewport(0, 0, width, height);
    
    // Initialize with the identity matrix ...
    glusMatrix4x4Identityf(modelMatrix);
    // ... and rotate the cube at two axes that we do see some sides.
    glusMatrix4x4RotateRzRxRyf(modelMatrix, 0.0f, 45.0f, 45.0f);
    
    // This model matrix is a rigid body transform. So no need for the inverse, transposed matrix.
    glusMatrix4x4ExtractMatrix3x3f(normalMatrix, modelMatrix);
    
    glusMatrix4x4Perspectivef(modelViewProjectionMatrix, 40.0f, (GLfloat) width / (GLfloat) height, 1.0f, 100.0f);
    
    glusMatrix4x4LookAtf(viewMatrix, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    // Here we create the view projection matrix ...
    glusMatrix4x4Multiplyf(modelViewProjectionMatrix, modelViewProjectionMatrix, viewMatrix);
    // ... and now the final model view projection matrix.
    glusMatrix4x4Multiplyf(modelViewProjectionMatrix, modelViewProjectionMatrix, modelMatrix);
    
    glUniformMatrix4fv(g_modelViewProjectionMatrixLocation, 1, GL_FALSE, modelViewProjectionMatrix);
    
    // Set the normal matrix.
    glUniformMatrix3fv(g_normalMatrixLocation, 1, GL_FALSE, normalMatrix);
}

GLUSboolean update(GLUSfloat time)
{
    // Now also clearing the depth buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDrawElements(GL_TRIANGLES, g_numberIndicesCube, GL_UNSIGNED_INT, 0);
    
    return GLUS_TRUE;
}

GLUSvoid terminate(GLUSvoid)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (g_verticesVBO)
    {
        glDeleteBuffers(1, &g_verticesVBO);
        
        g_verticesVBO = 0;
    }
    
    if (g_normalsVBO)
    {
        glDeleteBuffers(1, &g_normalsVBO);
        
        g_normalsVBO = 0;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    if (g_indicesVBO)
    {
        glDeleteBuffers(1, &g_indicesVBO);
        
        g_indicesVBO = 0;
    }
    
    glBindVertexArray(0);
    
    if (g_vao)
    {
        glDeleteVertexArrays(1, &g_vao);
        
        g_vao = 0;
    }
    
    glUseProgram(0);
    
    glusProgramDestroy(&g_program);
}

int main(int argc, char* argv[])
{
    EGLint eglConfigAttributes[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 0,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };
    
    EGLint eglContextAttributes[] = {
        EGL_CONTEXT_MAJOR_VERSION, 3,
        EGL_CONTEXT_MINOR_VERSION, 2,
        EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_TRUE,
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
    };
    
    glusWindowSetInitFunc(init);
    
    glusWindowSetReshapeFunc(reshape);
    
    glusWindowSetUpdateFunc(update);
    
    glusWindowSetTerminateFunc(terminate);
    
    if (!glusWindowCreate("Simple Cube", 800, 600, GLUS_FALSE, GLUS_FALSE, eglConfigAttributes, eglContextAttributes, 0))
    {
        printf("Could not create window!\n");
        return -1;
    }
    
    glusWindowRun();
    
    return 0;
}
