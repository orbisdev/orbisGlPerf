#ifndef RENDERSTATS_H
#define RENDERSTATS_H

void ResetRenderStats();
void LogDrawCall(uint32_t vertices, uint32_t triangles);
uint32_t GetVertexCount();
uint32_t GetTriangleCount();
uint32_t GetDrawCallCount();

#endif