/*
 *	orbisGlPerf sample for PlayStation 4 
 *  orginal work from rasperf3d https://www.bigmessowires.com/2014/10/06/raspberry-pi-3d-performance-demo/
 *	Copyright (C) 2018 Port to liborbis Antonio Jose Ramos Marquez (aka bigboss) @psxdev on twitter
 *  Repository https://github.com/orbisdev/samples/orbisGlPerf
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debugnet.h>

#include <kernel.h>
#include <systemservice.h>
#include <orbis2d.h>
#include <orbisPad.h>
#include <orbisKeyboard.h>
#include <orbisAudio.h>
#include <modplayer.h>
#include <sys/fcntl.h>
#include <ps4link.h>
#include <orbisFile.h>
#include <orbisGl.h>
#include "bitmap.h"
#include "ktx.h"
#include "vecmath.h"
#include "font.h"
#include "cube_model.h"
#include "frog_model.h"
#include "renderStats.h"
#include "shaderLoader.h"


#ifdef __cplusplus
extern "C" {
#endif

Orbis2dConfig *conf;
OrbisPadConfig *confPad;

typedef struct OrbisGlobalConf
{
	Orbis2dConfig *conf;
	OrbisPadConfig *confPad;
	OrbisAudioConfig *confAudio;
	OrbisKeyboardConfig *confKeyboard;
	ps4LinkConfiguration *confLink;
	int orbisLinkFlag;
}OrbisGlobalConf;

OrbisGlobalConf *myConf;

typedef enum {
    FIRST_MODEL_TYPE = 0,
    CUBE_MODEL = 0,
    FROG_MODEL,
    KID_MODEL,
    TREX_MODEL,
    ROBOT_MODEL,
    NUM_MODEL_TYPES  
} ModelType;

struct ModelInfo
{
    float* pVertexData;
    uint16_t* pIndexData;
    GLuint vertexBuffer;
    GLuint indexBuffer;  
    GLuint modelTexture;
    uint32_t numIndices;
    uint32_t numVerts;
};

struct RenderState 
{
    uint32_t fbWidth;
    uint32_t fbHeight;
    
    uint32_t numObjects;
    float yaw;

    bool showStats;
    bool backFaceCull;
    bool depthTest;
    bool renderLines;
    bool linearFiltering;
    bool mipmapping;
    float cameraDistance;
    float cameraYaw;
    bool cameraLookAway;
    bool multisampling;
    
    uint8_t shaderType;
    ShaderInfo shaderInfo[NUM_SHADER_TYPES];

    uint8_t modelType;
    ModelInfo modelInfo[NUM_MODEL_TYPES];
};

static RenderState rs;

bool InitShaderProgram()
{
    for (uint8_t t = FIRST_SHADER_TYPE; t < NUM_SHADER_TYPES; t++)
    {
        LoadShaderByType((ShaderType)t, &rs.shaderInfo[t]);
    }
    
    return true;
}
void InitModelBuffers()
{
    // cube: model data is in header file
    ModelInfo* m  = &rs.modelInfo[CUBE_MODEL];
    m->pVertexData = 0;
    m->pIndexData = 0;

    glGenBuffers(1, &m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), cube_verts, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);  

    m->numIndices = sizeof(cube_indices) / sizeof(uint16_t);
    m->numVerts = sizeof(cube_verts) / (sizeof(float)*8);

    // frog: model data is in header file
    m  = &rs.modelInfo[FROG_MODEL];
    m->pVertexData = 0;
    m->pIndexData = 0;

    glGenBuffers(1, &m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(frog_verts), frog_verts, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(frog_indices), frog_indices, GL_STATIC_DRAW);  

    m->numIndices = sizeof(frog_indices) / sizeof(uint16_t);
    m->numVerts = sizeof(frog_verts) / (sizeof(float)*8);

    // kid: too large to compile from a header file - load from an external binary file
    m  = &rs.modelInfo[KID_MODEL];
    int pFile = orbisOpen("host0:orbisGlPerf/models/kid.dat",O_RDONLY,0);
    if (pFile<=0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Couldn't open kid.dat\n");		
        return;
    } 

    ;
	if(orbisRead(pFile,&m->numVerts, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numVerts in kid.dat\n");
		orbisClose(pFile);		
		return;
	}
    uint32_t vertexBufferSize = m->numVerts * sizeof(float) * 8;
    m->pVertexData = (float*)malloc(vertexBufferSize);
    ;
	if(orbisRead(pFile,m->pVertexData, vertexBufferSize)!=vertexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pVertexData in kid.dat\n");
		orbisClose(pFile);		
		return;
	}
    ;
	if(orbisRead(pFile,&m->numIndices, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numIndices in kid.dat\n");
		orbisClose(pFile);		
		return;
	}
    uint32_t indexBufferSize = m->numIndices * sizeof(uint16_t);
    m->pIndexData = (uint16_t*)malloc(indexBufferSize);
    if(orbisRead(pFile,m->pIndexData, indexBufferSize)!=indexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pIndexData in kid.dat\n");
		orbisClose(pFile);		
		return;
	}
    orbisClose(pFile);

    glGenBuffers(1, &m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, m->pVertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, m->pIndexData, GL_STATIC_DRAW); 

    // t-rex: too large to compile from a header file - load from an external binary file
    m  = &rs.modelInfo[TREX_MODEL];
    pFile = orbisOpen("host0:orbisGlPerf/models/trex.dat",O_RDONLY,0);
	if (pFile <=0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Couldn't open trex.dat\n");		
		return;
    } 

    if(orbisRead(pFile,&m->numVerts, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numVerts in trex.dat\n");
		orbisClose(pFile);				
		return;
	}
    vertexBufferSize = m->numVerts * sizeof(float) * 8;
    m->pVertexData = (float*)malloc(vertexBufferSize);
    if(orbisRead(pFile,m->pVertexData, vertexBufferSize)!=vertexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pVertexData in trex.dat\n");
		orbisClose(pFile);				
		return;
	}
    if(orbisRead(pFile,&m->numIndices, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numIndices in trex.dat\n");
		orbisClose(pFile);		
		return;
	}
    indexBufferSize = m->numIndices * sizeof(uint16_t);
    m->pIndexData = (uint16_t*)malloc(indexBufferSize);
    if(orbisRead(pFile,m->pIndexData, indexBufferSize)!=indexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pIndexData in trex.dat\n");
		orbisClose(pFile);		
		return;
	}
    orbisClose(pFile); 

    // transform the data
    /*for (uint32_t i=0; i<m->numVerts; i++)
    {
        m->pVertexData[8*i] *= 0.017f;
        m->pVertexData[8*i+1] *= 0.017f;
        m->pVertexData[8*i+2] *= 0.017f;
    }

    // write out the transformed data
    pFile = fopen("trex2.dat", "wb");
    if (pFile == NULL)
    {
        printf("Couldn't open trex2.dat\n");
        return;
    }    

    fwrite(&m->numVerts, sizeof(uint32_t), 1, pFile);
    fwrite(m->pVertexData, vertexBufferSize, 1, pFile);
    fwrite(&m->numIndices, sizeof(uint32_t), 1, pFile);
    fwrite(m->pIndexData, indexBufferSize, 1, pFile);
    fclose(pFile);
    printf("wrote trex2.dat\n");*/
    
    glGenBuffers(1, &m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, m->pVertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, m->pIndexData, GL_STATIC_DRAW); 

    // robot: too large to compile from a header file - load from an external binary file
    m = &rs.modelInfo[ROBOT_MODEL];
    pFile = orbisOpen("host0:orbisGlPerf/models/robot.dat",O_RDONLY,0);
	
    if (pFile<=0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Couldn't open robot.dat\n");		
        return;
    } 

    if(orbisRead(pFile,&m->numVerts, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numVerts in robot.dat\n");
		orbisClose(pFile);		
		return;
	}
    vertexBufferSize = m->numVerts * sizeof(float) * 8;
    m->pVertexData = (float*)malloc(vertexBufferSize);
    if(orbisRead(pFile,m->pVertexData, vertexBufferSize)!=vertexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pVertexData in robot.dat\n");
		orbisClose(pFile);		
		return;
	}
    if(orbisRead(pFile,&m->numIndices, sizeof(uint32_t))!=sizeof(uint32_t))
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->numIndices in robot.dat\n");
		orbisClose(pFile);		
		return;
	}
    indexBufferSize = m->numIndices * sizeof(uint16_t);
    m->pIndexData = (uint16_t*)malloc(indexBufferSize);
    if(orbisRead(pFile,m->pIndexData, indexBufferSize)!=indexBufferSize)
	{
		debugNetPrintf(DEBUG,"[ORBISGLPERF] wrong m->pIndexData in robot.dat\n");
		orbisClose(pFile);		
		return;
	}
    orbisClose(pFile);
    
    glGenBuffers(1, &m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m->vertexBuffer); 
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, m->pVertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, m->pIndexData, GL_STATIC_DRAW); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   
}

void InitModel()
{
    InitModelBuffers();
    rs.modelInfo[CUBE_MODEL].modelTexture = LoadKTX("host0:orbisGlPerf/textures/cube.ktx");
    rs.modelInfo[FROG_MODEL].modelTexture = LoadKTX("host0:orbisGlPerf/textures/frog.ktx");
    rs.modelInfo[KID_MODEL].modelTexture = LoadKTX("host0:orbisGlPerf/textures/kid.ktx");
    rs.modelInfo[TREX_MODEL].modelTexture = LoadKTX("host0:orbisGlPerf/textures/trex.ktx");
    rs.modelInfo[ROBOT_MODEL].modelTexture = LoadKTX("host0:orbisGlPerf/textures/robot.ktx");
    if (!rs.modelInfo[CUBE_MODEL].modelTexture || 
        !rs.modelInfo[FROG_MODEL].modelTexture || 
        !rs.modelInfo[KID_MODEL].modelTexture || 
        !rs.modelInfo[TREX_MODEL].modelTexture || 
        !rs.modelInfo[ROBOT_MODEL].modelTexture)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF]Failed to load the model textures.\n");
    }

    InitShaderProgram();
}

void FreeModel()
{
    for (uint8_t t = FIRST_SHADER_TYPE; t < NUM_SHADER_TYPES; t++)
    {
        glDeleteShader(rs.shaderInfo[t].shaderProgram);
    }

    for (uint8_t t = FIRST_MODEL_TYPE; t < NUM_MODEL_TYPES; t++)
    {
        ModelInfo& m = rs.modelInfo[t];
        glDeleteBuffers(1, &m.vertexBuffer);
        glDeleteBuffers(1, &m.indexBuffer);
        if (m.pVertexData)
            free(m.pVertexData);
        if (m.pIndexData)
            free(m.pIndexData);
        glDeleteTextures(1, &m.modelTexture);
    }
}

void Render()
{
    static mat4 proj(mat4::perspective(45, ((float) rs.fbWidth)/rs.fbHeight, 1, 1000));

    // calculate the view matrix
    vec4 lookPos(0,2.3f,rs.cameraLookAway ? 100 : 0,1);
    vec4 eye = mat4::rotate(rs.cameraYaw, vec4(0,1,0,1)) * vec4(0,0,rs.cameraDistance,1);
    mat4 view(mat4::lookAt(eye, lookPos, vec4(0,1,0,1)));

    // light position is fixed in world space
    vec4 lightPosition_worldspace = vec4(-30,10,20,1);
    vec4 lightPosition_viewspace = view * lightPosition_worldspace;
 
    // bind the shader program and set the uniform shader parameters
    ShaderInfo& currentShader = rs.shaderInfo[rs.shaderType];
    glUseProgram(currentShader.shaderProgram);
    glUniform3fv(currentShader.lightLoc, 1, &lightPosition_viewspace.x); // only the light's XYZ is passed
    glUniform1i(currentShader.texSamplerLoc, 0); // sample from texture unit #0

    // bind the model's texture to texture unit #0
    ModelInfo& currentModel = rs.modelInfo[rs.modelType];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentModel.modelTexture);

    // bind the vertex and index buffer
    glBindBuffer(GL_ARRAY_BUFFER, currentModel.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentModel.indexBuffer);

    // set OpenGL states
    if (rs.backFaceCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (rs.depthTest)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
    glClearColor ( 0.1f, 0.2f, 0.3f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    // set vertex data pointers
    const uint32_t posSize = 3;
    const uint32_t normSize = 3;
    const uint32_t uvSize = 2;
    const uint32_t vertBytes = sizeof(float) * (posSize + normSize + uvSize);

    glEnableVertexAttribArray(currentShader.vertLoc);
    glVertexAttribPointer(currentShader.vertLoc, posSize, GL_FLOAT, false, vertBytes, 
        (const void*)0);

    glEnableVertexAttribArray(currentShader.normalLoc);
    glVertexAttribPointer(currentShader.normalLoc, normSize, GL_FLOAT, false, vertBytes, 
        (const void*)(posSize * sizeof(float)));

    glEnableVertexAttribArray(currentShader.texcoordLoc);
    glVertexAttribPointer(currentShader.texcoordLoc, uvSize, GL_FLOAT, false, vertBytes, 
        (const void*)((posSize + normSize) * sizeof(float)));

    // calculate how many objects to draw per row
    uint32_t rowSize = 1;
    while (rowSize * rowSize < rs.numObjects)
        rowSize++;
    const float rowScale = 25.0f;
    float rowStep = rs.numObjects == 1 ? rowScale : rowScale / (rowSize - 1);

    // draw the objects in a grid layout
    uint32_t numObjectsDrawn = 0;
    for (int x=0; x<rowSize && numObjectsDrawn < rs.numObjects; x++)
    {
        float objX = (rs.numObjects == 1) ? 0 : (1.5f * (-rowScale/2.0f + x*rowStep));

        for (int y=0; y<rowSize && numObjectsDrawn < rs.numObjects; y++)
        {    
            float objXs = objX + (y%2)*rowStep/2.0f;
            float objY = (rs.numObjects == 1) ? 0 : (-rowScale/2.0f + y*rowStep);

            // construct a yaw for this object, by combining the global yaw with the grid position
            // calculate the model matrix from the yaw
            float yaw = rs.yaw + x*40 + y*50;
            mat4 modelRotate(mat4::rotate(yaw, vec4(0,1,0,1)));
            mat4 modelTranslate(mat4::translate(vec4(objXs,objY,0,1)));
            mat4 model = modelTranslate * modelRotate;
            
            // calculate the matrices
            mat4 mv = view * model;
            mat4 mvp = proj * view * model;

            // set the per-model parameters
            glUniformMatrix4fv(currentShader.mvLoc, 1, false, &mv.x.x);
            glUniformMatrix4fv(currentShader.mvpLoc, 1, false, &mvp.x.x);

            // draw!
            GLenum mode = rs.renderLines ? GL_LINE_STRIP : GL_TRIANGLES;
            glDrawElements(mode, currentModel.numIndices, GL_UNSIGNED_SHORT, (void*)0);
            LogDrawCall(currentModel.numVerts, currentModel.numIndices/3);

            numObjectsDrawn++;
        }
    } 

    // clean up state - unbind OpenGL resources
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ApplyTextureFilter()
{
    GLenum minFilter;
    GLenum magFilter;
    if (rs.linearFiltering)
    {
        magFilter = GL_LINEAR;
        if (rs.mipmapping)
            minFilter = GL_LINEAR_MIPMAP_NEAREST;
        else
            minFilter = GL_LINEAR;
    }
    else
    {
        magFilter = GL_NEAREST;
        if (rs.mipmapping)
            minFilter = GL_NEAREST_MIPMAP_NEAREST;
        else
            minFilter = GL_NEAREST;
    }

    glBindTexture(GL_TEXTURE_2D, rs.modelInfo[rs.modelType].modelTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glBindTexture(GL_TEXTURE_2D, 0);
}




bool flag=true;



void updateController()
{
	int ret;
	unsigned int buttons=0;
	ret=orbisPadUpdate();
	if(ret==0)
	{
		if(orbisPadGetButtonPressed(ORBISPAD_L2|ORBISPAD_R2) || orbisPadGetButtonHold(ORBISPAD_L2|ORBISPAD_R2))
		{
			buttons=orbisPadGetCurrentButtonsPressed();
			buttons&= ~(ORBISPAD_L2|ORBISPAD_R2);
			orbisPadSetCurrentButtonsPressed(buttons);
            rs.mipmapping = !rs.mipmapping;
            ApplyTextureFilter();
			debugNetPrintf(DEBUG,"[ORBISGLPERF] mipmapping=%d\n",rs.mipmapping);
			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_L1|ORBISPAD_R1) )
		{
			buttons=orbisPadGetCurrentButtonsPressed();
			buttons&= ~(ORBISPAD_L1|ORBISPAD_R1);
			orbisPadSetCurrentButtonsPressed(buttons);
			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_L1|ORBISPAD_R2) || orbisPadGetButtonHold(ORBISPAD_L1|ORBISPAD_R2))
		{
			buttons=orbisPadGetCurrentButtonsPressed();
			buttons&= ~(ORBISPAD_L1|ORBISPAD_R2);
			orbisPadSetCurrentButtonsPressed(buttons);
			
			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_L2|ORBISPAD_R1) || orbisPadGetButtonHold(ORBISPAD_L2|ORBISPAD_R1) )
		{
			buttons=orbisPadGetCurrentButtonsPressed();
			buttons&= ~(ORBISPAD_L2|ORBISPAD_R1);
			orbisPadSetCurrentButtonsPressed(buttons);
			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_UP))
		{
            rs.modelType++;
            if (rs.modelType == NUM_MODEL_TYPES)
                rs.modelType = FIRST_MODEL_TYPE;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] modelType=%d\n",rs.modelType);
		}
		if(orbisPadGetButtonPressed(ORBISPAD_DOWN))
		{
            rs.linearFiltering = !rs.linearFiltering;
            ApplyTextureFilter();
            
			debugNetPrintf(DEBUG,"[ORBISGLPERF] linearFiltering=%d\n",rs.linearFiltering);
		}						
		if(orbisPadGetButtonPressed(ORBISPAD_RIGHT))
		{
            rs.shaderType++;
            if (rs.shaderType == NUM_SHADER_TYPES)
                rs.shaderType = FIRST_SHADER_TYPE;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] shaderType=%d\n",rs.shaderType);
			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_LEFT))
		{
            rs.numObjects = (rs.numObjects > 0) ? (rs.numObjects - 1) : 0;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] numObjects=%d\n",rs.numObjects);	
		}
		if(orbisPadGetButtonPressed(ORBISPAD_TRIANGLE))
		{
			debugNetPrintf(DEBUG,"[ORBISGLPERF] Triangle pressed exit\n");
			flag=0;	
		}
		if(orbisPadGetButtonPressed(ORBISPAD_CIRCLE))
		{
            rs.depthTest = !rs.depthTest;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] depthTest=%d\n",rs.depthTest);	
		}
		if(orbisPadGetButtonPressed(ORBISPAD_CROSS))
		{
            rs.renderLines = !rs.renderLines;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] renderLines=%d\n",rs.renderLines);	
		}
		if(orbisPadGetButtonPressed(ORBISPAD_SQUARE))
		{
            rs.backFaceCull = !rs.backFaceCull;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] backFaceCull=%d\n",rs.backFaceCull);
		}
		if(orbisPadGetButtonPressed(ORBISPAD_L1))
		{
            rs.showStats = !rs.showStats;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] showStats=%d\n",rs.showStats);			
		}
		if(orbisPadGetButtonPressed(ORBISPAD_L2))
		{
            rs.cameraLookAway = !rs.cameraLookAway;  
			debugNetPrintf(DEBUG,"[ORBISGLPERF] cameraLookAway=%d\n",rs.cameraLookAway);						
		}
		if(orbisPadGetButtonPressed(ORBISPAD_R1))
		{
            rs.cameraYaw += 30.0f;
            if (rs.cameraYaw > 90.0f)
                rs.cameraYaw = -90.0f;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] cameraYaw=%d\n",rs.cameraYaw);						
		}
		if(orbisPadGetButtonPressed(ORBISPAD_R2))
		{
            rs.cameraDistance -= 5.0f;
            if (rs.cameraDistance < 5.0f)
                rs.cameraDistance = 60.0f;
			debugNetPrintf(DEBUG,"[ORBISGLPERF] cameraDistance=%d\n",rs.cameraDistance);						
		}	
	}
}
void finishApp()
{
	
	orbisAudioFinish();
	orbisKeyboardFinish();
	orbisGlFinish();
	orbisPadFinish();
	orbisFileFinish();
	ps4LinkFinish();
}
bool initAppGl()
{
	int ret;
	ret=orbisGlInit(ATTR_ORBISGL_WIDTH,ATTR_ORBISGL_HEIGHT);
	if(ret>0)
	{
		
			glViewport(0, 0, ATTR_ORBISGL_WIDTH, ATTR_ORBISGL_HEIGHT);
			ret=glGetError();
			if(ret)
			{
				debugNetPrintf(ERROR,"[ORBISGLPERF] glViewport failed: 0x%08X\n",ret);
				return false;
			}
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			ret=glGetError();
			if(ret)
			{
				debugNetPrintf(ERROR,"[ORBISGLPERF] glClearColor failed: 0x%08X\n",ret);
				return false;
			}
			
			
		
			return true;
	}
	return false;
}
bool initApp()
{
	int ret;
	sceSystemServiceHideSplashScreen();
	//more library initialiazation here pad,filebroser,audio,keyboard, etc
	//....
	orbisFileInit();
	ret=orbisPadInitWithConf(myConf->confPad);
	if(ret)
	{
		confPad=orbisPadGetConf();
		ret=orbisAudioInitWithConf(myConf->confAudio);
		if(ret==1)
		{
			ret=orbisKeyboardInitWithConf(myConf->confKeyboard);
			if(ret!=1)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	if(!initAppGl())
	{
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	int ret;


	uintptr_t intptr=0;
	sscanf(argv[1],"%p",&intptr);
	myConf=(OrbisGlobalConf *)intptr;
	ret=ps4LinkInitWithConf(myConf->confLink);
	if(!ret)
	{
		ps4LinkFinish();
		return 0;
	}
	debugNetPrintf(INFO,"[ORBISGLPERF] let's go\n");	
	
	
	
	//init libraries 
	flag=initApp();
	
    
	
	Mod_Init(0);
	Mod_Load("host0:estrayk_-_xmas.mod");
	Mod_Play();
	orbisAudioResume(0);
	
	/*int x=ATTR_ORBISGL_WIDTH/2;
	int y=ATTR_ORBIS_HEIGHT/2;
	int w=50;
	int h=50;
	float color[4]={1.0f,0.0f,0.0f.1.0f}; //red*/
	
	if(flag)
	{
		
	    rs.fbWidth = ATTR_ORBISGL_WIDTH;
	    rs.fbHeight = ATTR_ORBISGL_HEIGHT;
	    rs.numObjects = 81;
	    rs.showStats = false;
	    rs.backFaceCull = true;
	    rs.depthTest = false;
	    rs.renderLines = false;
	    rs.linearFiltering = true;
	    rs.mipmapping = true;
	    rs.cameraDistance = 40.0f;
	    rs.cameraYaw = 0.0f;
	    rs.shaderType = UNTEXTURED_GOURAUD;
	    rs.cameraLookAway = false;
	    rs.modelType = FIRST_MODEL_TYPE;
	    rs.multisampling = false;
		
	    // load the model, texture, and shader
	    InitModel();

	    // load the font resources
		InitFont(rs.fbWidth, rs.fbHeight);
		
		
		
		
	}
	
	SceKernelTimeval now,then;
	debugNetPrintf(INFO,"[ORBISGLPERF] init done \n");
	sceKernelGettimeofday(&then);	
	debugNetPrintf(INFO,"[ORBISGLPERF] tv_sec=%d tv_usec=%d\n",then.tv_sec,then.tv_usec);
	
	sceKernelGettimeofday(&then);	
	debugNetPrintf(INFO,"[ORBISGLPERF] tv_sec=%d tv_usec=%d\n",then.tv_sec,then.tv_usec);
	
	
	
	while(flag)
	{
		sceKernelGettimeofday(&now);	
		uint32_t frameTimeMicrosecs=((now.tv_sec - then.tv_sec) * 1000000) + 
                                    (now.tv_usec - then.tv_usec);
		then=now;
		updateController();
		
		/*glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(programId);
		
		glVertexAttribPointer(s_xyz_loc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), s_obj_vertices);
		
		glVertexAttribPointer(s_uv_loc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &s_obj_vertices[3]);
		
		glEnableVertexAttribArray(s_xyz_loc);
	
		glEnableVertexAttribArray(s_uv_loc);
		
	//	orbisGlDrawRectangle(x,y,w,h,color);
		
		glActiveTexture(GL_TEXTURE0);
		
		glBindTexture(GL_TEXTURE_2D, textureId);
		
		glUniform1i(s_sampler_loc, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, s_obj_indices);*/
		
		
		
        // update object transforms using the frame time - this ensures animation won't appear
        // to slow down when the frame rate drops 
		rs.yaw += 0.0001f * frameTimeMicrosecs;

        // draw the scene
        Render();

        // update and display statistics
        uint32_t textRow = 0;
        char textBuf[100] = { 0 };  
		//if(frameTimeMicrosecs)
        float fps = 1000000.0f/frameTimeMicrosecs;
        uint32_t draws = GetDrawCallCount(), tris = GetTriangleCount(), verts = GetVertexCount();
        uint32_t trisPerSec = tris * fps;
        ResetRenderStats();

        sprintf(textBuf, "FPS %2.1f", fps);
		AddText(textBuf, 0, 20*textRow++);
        sprintf(textBuf, "TRIS/SEC %4.2fM  ",(float)trisPerSec/1000000);
		AddText(textBuf, 0, 20*textRow++);
        sprintf(textBuf, "TRIS/FRAME %4.2fK  ",(float)tris/1000);
		AddText(textBuf, 0, 20*textRow++);
		

        if (rs.showStats)
        {
            sprintf(textBuf, "%d VERTS/FRAME", verts);
            AddText(textBuf, 0, 20*textRow++); 

            sprintf(textBuf, "LEFT +/-: OBJECT COUNT [%d]", rs.numObjects);
            AddText(textBuf, 0, 20*textRow++);             

            sprintf(textBuf, "UP: OBJECT COMPLEXITY [%s]", 
                rs.modelType == CUBE_MODEL ? "12 TRIS" : 
                rs.modelType == FROG_MODEL ? "496 TRIS" :
                rs.modelType == KID_MODEL ? "5682 TRIS" :
                rs.modelType == TREX_MODEL ? "18940 TRIS" :
                "55593 TRIS");
            AddText(textBuf, 0, 20*textRow++); 

            //sprintf(textBuf, "F: FRAMEBUFFER [%d X %d]", rs.fbWidth, rs.fbHeight);
            //AddText(textBuf, 0, 20*textRow++);

            //sprintf(textBuf, "P: MULTISAMPLING [%s]", rs.multisampling ? "ON" : "OFF");
            //AddText(textBuf, 0, 20*textRow++); 

            sprintf(textBuf, "RIGHT: SHADER [%s]", GetShaderNameByType((ShaderType)rs.shaderType));
            AddText(textBuf, 0, 20*textRow++);  

            sprintf(textBuf, "DOWN: TEXTURE FILTER [%s]", rs.linearFiltering ? "LINEAR" : "NEAREST");
            AddText(textBuf, 0, 20*textRow++);   

            sprintf(textBuf, "L2+R2: MIPMAPS [%s]", rs.mipmapping ? "ON" : "OFF");
            AddText(textBuf, 0, 20*textRow++);   

            sprintf(textBuf, "SQUARE: BACKFACE CULLING [%s]", rs.backFaceCull ? "ON" : "OFF");
            AddText(textBuf, 0, 20*textRow++);

            sprintf(textBuf, "CIRCLE: DEPTH TEST [%s]", rs.depthTest ? "ON" : "OFF");
            AddText(textBuf, 0, 20*textRow++);       

            sprintf(textBuf, "CROSS: WIREFRAME [%s]", rs.renderLines ? "ON" : "OFF");
            AddText(textBuf, 0, 20*textRow++);    

            sprintf(textBuf, "R2: CAMERA DISTANCE [%d]", (int)rs.cameraDistance);
            AddText(textBuf, 0, 20*textRow++);   

            sprintf(textBuf, "R1: CAMERA YAW [%d]", (int)rs.cameraYaw);
            AddText(textBuf, 0, 20*textRow++); 

            sprintf(textBuf, "L2: CAMERA LOOK [%s]", rs.cameraLookAway ? "AWAY" : "TOWARDS");
            AddText(textBuf, 0, 20*textRow++);      

            AddText("L1: STATS DISPLAY [ON]", 0, 20*textRow++);

            AddText("Triangle: EXIT", 0, 20*textRow++);   
        }

        RenderText();
		
		orbisGlSwapBuffers();
	}

	orbisAudioPause(0);
	Mod_End();
	glClear(GL_COLOR_BUFFER_BIT);
	orbisGlSwapBuffers();
	
	//finish libraries
	finishApp();
	return EXIT_SUCCESS;
	
}

#ifdef __cplusplus
}
#endif