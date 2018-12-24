#include <stdint.h>

struct RenderStats
{
    uint32_t drawCalls;
    uint32_t vertices;
    uint32_t triangles;
};

static RenderStats stats;

void ResetRenderStats()
{
    stats.vertices = 0;
    stats.triangles = 0;
    stats.drawCalls = 0;
}

void LogDrawCall(uint32_t vertices, uint32_t triangles)
{
    stats.vertices += vertices;
    stats.triangles += triangles;
    stats.drawCalls++;
}

uint32_t GetVertexCount()
{
    return stats.vertices;
}

uint32_t GetTriangleCount()
{
    return stats.triangles;
}

uint32_t GetDrawCallCount()
{
    return stats.drawCalls;
}