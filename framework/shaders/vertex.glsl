#version 400 
in  vert_position;
in  vert_normal;
out  outColor;
uniform mat4 ModelView;
uniform mat4 NormalMatrix;
void toEyeCoordidp671840( out vec4 eyepos,out vec4 eyenormal, in vec4 position, in vec4 normal)
{
vec4 opidp892960 = normal*NormalMatrix;
vec4 opidp823360 = position*ModelView;
eyepos = opidp823360;
eyenormal = opidp892960;
}
void main()
{
 vec4 eyeposidp671840;
vec4 eyenormalidp671840;
toEyeCoordidp671840(eyeposidp671840,eyenormalidp671840,vert_position,vert_normal);
gl_Position = eyeposidp671840;
outColor = eyenormalidp671840;
}
 