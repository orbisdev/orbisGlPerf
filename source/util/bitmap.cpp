#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <debugnet.h>
#include <orbisFile.h>
#include <GLES2/gl2.h>
#include "bitmap.h"
#pragma pack(1)
struct BMPHeader 
{
    uint16_t  type; 
    uint32_t  size; 
    uint16_t  unused; 
    uint16_t  unused2; 
    uint32_t  offset; 
}; 

struct BMPInfo 
{
    uint32_t  size;
    uint32_t  width;
    uint32_t  height;
    uint16_t  planes;
    uint16_t  bits;
    uint32_t  compression;
    uint32_t  imageSize;
    uint32_t  xScale;
    uint32_t  yScale;
    uint32_t  colors;
    uint32_t  importantColors;
    uint8_t   rgb[4];
};

#pragma pack(8)

GLuint LoadBMP(const char* filename)
{
    int pFile = orbisOpen(filename, O_RDONLY,0);
    if (pFile <=0)
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] Couldn't open %s\n", filename);
        return 0;
    }    

    BMPHeader bitmapHeader;
    if (orbisRead(pFile,&bitmapHeader,sizeof(BMPHeader)) != sizeof(BMPHeader))
    {
        orbisClose(pFile);
        return 0;
    }

    uint32_t infoSize = bitmapHeader.offset - sizeof(BMPHeader);
    BMPInfo* pBitmapInfo = (BMPInfo *) malloc(sizeof(GLbyte)*infoSize);
    if (orbisRead(pFile,pBitmapInfo,infoSize) != infoSize)
    {
        free(pBitmapInfo);
        orbisClose(pFile);
        return 0;
    }

    uint32_t width = pBitmapInfo->width;
    uint32_t height = pBitmapInfo->height;
    uint32_t imageSize = pBitmapInfo->imageSize;
    uint32_t rowBytes = (width * pBitmapInfo->bits + 7) / 8;
    if (imageSize == 0)
        imageSize = rowBytes * height;
    uint32_t bitDepth = pBitmapInfo->bits;
    free(pBitmapInfo);
    
    GLbyte* pBits = (GLbyte*)malloc(sizeof(GLbyte)*imageSize);
    if (orbisRead(pFile,pBits,imageSize) != imageSize)
    {
        free(pBits);
        orbisClose(pFile);
        return 0;
    }

    orbisClose(pFile);

    // BMP image data is stored "upside down", starting at the bottom-left corner.
    // Mirror the image data vertically to be consistent with other image formats.
    // (Alternatively, invert the V texture coordinate for all drawing operations.) 
    for (uint32_t row = 0; row < height/2; row++)
    {
        uint32_t mirrowRow = (height - 1) - row;

        for (uint32_t x = 0; x < rowBytes; x++)
        {
            uint8_t temp = pBits[row*rowBytes + x];
            pBits[row*rowBytes + x] = pBits[mirrowRow*rowBytes + x];
            pBits[mirrowRow*rowBytes + x] = temp;
        }
    }

    // OpenGL ES on the Raspberry Pi doesn't seem to support GL_BGR color format.
    // convert the BMP's BGR colors to RGB. 
    if (bitDepth == 24)
    {
        for (uint32_t p = 0; p < imageSize; p += 3)
        {
            uint8_t temp = pBits[p];
            pBits[p] = pBits[p+2];
            pBits[p+2] = temp;
        }
    }

    // create an Open GL texture from the raw image data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLenum format;
    if (bitDepth == 24)
        format = GL_RGB;
    else if (bitDepth == 8)
        format = GL_ALPHA;
    else
    {
        debugNetPrintf(DEBUG,"[ORBISGLPERF] %s has unsupported bit depth: %d", filename, bitDepth);
        free(pBits);
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pBits);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT /*GL_CLAMP_TO_EDGE*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT /*GL_CLAMP_TO_EDGE*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(pBits);

    return textureID;
}