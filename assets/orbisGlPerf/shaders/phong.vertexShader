// input constants
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;

// input variables, different for each vertex
attribute vec3 vertPosition_modelspace;
attribute vec3 vertNormal_modelspace;
attribute vec2 vertTexCoord0;

// outputs
varying vec3 position_viewspace;
varying vec3 normal_viewspace;
varying vec2 texCoord0;

void main()
{
    // pass the texture coordinate unchanged
    texCoord0 = vertTexCoord0;

    // vertex position in viewspace is needed for lighting in the fragment shader
    position_viewspace = vec3(mvMatrix * vec4(vertPosition_modelspace, 1));

    // normal vector in viewspace is also needed for lighting in the fragment shader
    // this math is only correct if mvMatrix has a uniform scale! Otherwise use its inverse transpose.
    normal_viewspace = vec3(mvMatrix * vec4(vertNormal_modelspace,0)); 

    // OpenGL needs the fully-projected vertex position for rendering the triangle
    gl_Position = mvpMatrix * vec4(vertPosition_modelspace, 1);
}