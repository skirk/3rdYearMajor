import Framework as fw
from Framework import *

c = fw.Context()

c.printDB()

c.listCurrent()

c.addNode("toEyeCoord")
c.goDownALevel("toEyeCoord.0")
c.addInputSlot('Vertex_Pos', VEC4)
c.addInputSlot('Vertex_Norm', VEC3)
c.addOutputSlot('Eye_Pos', VEC4)
c.addOutputSlot('Eye_Norm', VEC3)

c.addNode('ModelViewMatrix')
c.addNode('NormalMatrix')
c.addNode('MultiplyMat4Vec4')
c.addNode('MultiplyMat3Vec3')

c.connectSlots('ModelViewMatrix.0.out1', 'MultiplyMat4Vec4.0.in1')
c.connectSlots('NormalMatrix.0.out1', 'MultiplyMat3Vec3.0.in1')
c.connectSlots('Vertex_Pos', 'MultiplyMat4Vec4.0.in2')
c.connectSlots('Vertex_Norm', 'MultiplyMat3Vec3.0.in2')

c.connectSlots('Eye_Pos', 'MultiplyMat4Vec4.0.out1')
c.connectSlots('Eye_Norm', 'MultiplyMat3Vec3.0.out1')
c.listCurrent()

c.writeNode("temporary/toEyeCoord.xml")

#Vertex shader
#c.addInputSlot("VertexPosition", VEC3);
#c.addInputSlot("VertexNormal", VEC3);
#c.addOutputSlot("LightIntensity", VEC3);
#c.addOutputSlot("gl_Position", VEC4);
#
#c.addNode('ModelView');
#c.addNode('ProjectionMatrix');
#c.addNode('NormalMatrix');
#c.addNode('Kd');
#c.addNode('Ld');
#c.addNode('LightPosition');
#
#c.addNode('dot')
#c.addNode('max')
#c.addNode('normalize')
#
#c.connectSlots(
#
#c.writeShader("temporary/shader.xml")
##p = fw.processor();
#p.process("graph.xsl", "temporary/shader.xml", "shaders/vertex.glsl");
