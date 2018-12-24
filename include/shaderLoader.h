#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GLES2/gl2.h>

typedef enum {
    FIRST_SHADER_TYPE = 0,
    PHONG = 0,
    GOURAUD,
    UNTEXTURED_PHONG,
    UNTEXTURED_GOURAUD,
    FLAT,
    NUM_SHADER_TYPES
} ShaderType;

struct ShaderInfo
{
    GLint shaderProgram;
    GLint vertLoc;
    GLint mvLoc;
    GLint mvpLoc;
    GLint lightLoc;
    GLint normalLoc;
    GLint texcoordLoc;
    GLint texSamplerLoc;
};

//GLint LoadShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
bool LoadShaderByType(ShaderType shaderType, ShaderInfo* shaderInfo);
const char* GetShaderNameByType(ShaderType shaderType);

#endif