#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLES2/gl2.h>

#include "shaderLoader.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <debugnet.h>
#include <orbisFile.h>
#include <orbisGl.h>

const char* shaderNames[NUM_SHADER_TYPES] = {
    "PER-PIXEL LIGHTING",
    "PER-VERTEX LIGHTING",
    "PER-PIXEL UNTEXTURED",
    "PER-VERTEX UNTEXTURED",
    "FLAT COLORED"
};

const char* shaderFilenames[NUM_SHADER_TYPES][2] = {
    { "host0:orbisGlPerf/shaders/phong.vertexShader", "host0:orbisGlPerf/shaders/phong.fragmentShader" },
    { "host0:orbisGlPerf/shaders/gouraud.vertexShader", "host0:orbisGlPerf/shaders/gouraud.fragmentShader" },
    { "host0:orbisGlPerf/shaders/phong.vertexShader", "host0:orbisGlPerf/shaders/untextured-phong.fragmentShader" },
    { "host0:orbisGlPerf/shaders/gouraud.vertexShader", "host0:orbisGlPerf/shaders/untextured-gouraud.fragmentShader" },
    { "host0:orbisGlPerf/shaders/flat.vertexShader", "host0:orbisGlPerf/shaders/flat.fragmentShader" }
};

/*const char* GetFileText(const char* filename)
{
    int pFile=orbisOpen(filename,O_RDONLY,0);

    if (pFile <=0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Failed to read shader file %s\n", filename);
        return 0;
    }

    // obtain file size:
    int32_t fileSize=orbisLseek(pFile , 0 , SEEK_END);
	orbisLseek(pFile,0,SEEK_SET);  // Seek back to start
	if(fileSize<0)
	{
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Failed to read shader file %s\n", filename);
        orbisClose(pFile);
		return NULL;
	}
	
    char* pText = (char*) malloc(sizeof(char)*fileSize+1);

    if (orbisRead(pFile,pText,fileSize) != fileSize)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Failed to read shader file %s\n", filename);
        orbisClose(pFile);
        free(pText);
        return 0;
    }
	orbisClose(pFile);
    // add null terminator to string
    pText[fileSize] = 0;

    return pText;
}

bool CompileShader(GLuint shader, const char* shaderSource)
{
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF]Failed to create a shader.\n");

        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) 
        {
            char* log = (char*)malloc(length);
            glGetShaderInfoLog(shader, length, NULL, log);
            debugNetPrintf(DEBUG,"[ORBISGLPERF] error log: %s\n", log);
            free(log);
        }

        return false;
    }

    return true;
}

GLint LoadShader(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
    // vertex shader
    debugNetPrintf(DEBUG,"[ORBISGLPERF] Compiling %s\n", vertexShaderFilename);
    const char* vsSource = GetFileText(vertexShaderFilename);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    if(!CompileShader(vs, vsSource))
	{
	    debugNetPrintf(DEBUG,"[ORBISGLPERF] Compiling failed with %s\n", vertexShaderFilename);
		
		return 0;
	}
    free((void*)vsSource);

    // fragment shader
    debugNetPrintf(DEBUG,"[ORBISGLPERF] Compiling jar %s\n", fragmentShaderFilename);
    const char* fsSource = GetFileText(fragmentShaderFilename);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    if(!CompileShader(fs, fsSource))
	{
	    debugNetPrintf(DEBUG,"[ORBISGLPERF] Compiling failed with %s\n", fragmentShaderFilename);
		
		return 0;
	}
    free((void*)fsSource);

    // shader program
    GLuint po = glCreateProgram();
    glAttachShader(po, vs);
    glAttachShader(po, fs);
    glLinkProgram(po);

    GLint status;
    glGetProgramiv(po, GL_LINK_STATUS, &status);
    if (status == 0) 
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Failed to link shader program.\n");

        GLint length;
        glGetProgramiv(po, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) 
        {
            char* log = (char *)malloc(length);
            glGetProgramInfoLog(po, length, NULL, log);
            debugNetPrintf(DEBUG,"[ORBISGLPERF]error log: %s\n", log);
            free(log);
        }

        return 0;
    }

    // Free shader resources
    glDeleteShader(vs);
    glDeleteShader(fs);
    debugNetPrintf(DEBUG,"[ORBISGLPERF] linked %s %s\n",vertexShaderFilename,fragmentShaderFilename);

    return po;
}
*/
bool LoadShaderByType(ShaderType shaderType, ShaderInfo* shaderInfo)
{
    GLint po = orbisGlCreateProgram(shaderFilenames[shaderType][0], shaderFilenames[shaderType][1]);    

	if(po==0)
	{
	    debugNetPrintf(DEBUG,"[ORBISGLPERF] program creation failed for %s %s\n",shaderFilenames[shaderType][0],shaderFilenames[shaderType][1]);
		return false;
	}
    shaderInfo->shaderProgram = po;
    // save the locations of the program inputs
    shaderInfo->vertLoc = glGetAttribLocation( po, "vertPosition_modelspace" );
    //assert(shaderInfo->vertLoc != -1);
    shaderInfo->normalLoc = glGetAttribLocation( po, "vertNormal_modelspace" );
    //assert(shaderInfo->normalLoc != -1);
    shaderInfo->texcoordLoc = glGetAttribLocation( po, "vertTexCoord0" );
    //assert(shaderInfo->texcoordLoc != -1);
    shaderInfo->mvLoc = glGetUniformLocation( po, "mvMatrix" );
    //assert(shaderInfo->mvLoc != -1);
    shaderInfo->mvpLoc = glGetUniformLocation( po, "mvpMatrix" );
    //assert(shaderInfo->mvpLoc != -1);
    shaderInfo->lightLoc = glGetUniformLocation( po, "lightPosition_viewspace" );
    //assert(shaderInfo->lightLoc != -1);
    shaderInfo->texSamplerLoc = glGetUniformLocation( po, "textureSampler" );
    //assert(shaderInfo->texSamplerLoc != -1);

    debugNetPrintf(DEBUG,"[ORBISGLPERF] program %d created for %s %s\n",po,shaderFilenames[shaderType][0],shaderFilenames[shaderType][1]);
	
    return true;
}

const char* GetShaderNameByType(ShaderType shaderType)
{
    return shaderNames[shaderType];
}