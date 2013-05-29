#version 400 
in vec4node match root0vert_position;
in vec4node match root0vert_normal;
out vec4node match root0outColor;
uniform mat4 ModelView;
uniform mat4 NormalMatrix;
void toEyeCoordidp625440( out vec4 eyepos,out vec4 eyenormal, in vec4 position, in vec4 normal)
{
vec4 opidp873920 = 		
		asdasd
		normal OPERATOR 		
		asdasd
		NormalMatrix;
vec4 opidp795200 = 		
		asdasd
		position OPERATOR 		
		asdasd
		ModelView;
eyepos = opidp795200;
eyenormal = opidp873920;
}
void rootidp566720( out vec4 gl_Position,out vec4 outColor, in vec4 vert_position, in vec4 vert_normal)
{
output eyeposidp625440
output eyenormalidp625440
toEyeCoordidp625440(eyeposidp625440,eyenormalidp625440,input		
		asdasd
		vert_position,input		
		asdasd
		vert_normal);
gl_Position = ;
outColor = ;
}
void main()
{
 output gl_Positionidp566720
output outColoridp566720
rootidp566720(gl_Positionidp566720,outColoridp566720,input,input);
}
 