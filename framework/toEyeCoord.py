import Framework as fw
from nodetype import *
from slotvariable import *

c = fw.Context()

c.printDB()

c.listCurrent()

c.addInputSlot('position', VEC4)
c.addInputSlot('normal', VEC4)
c.addOutputSlot('eyepos', VEC4)
c.addOutputSlot('eyenormal', VEC4)

c.addNode('ModelView')
c.addNode('NormalMatrix')
c.addNode('MultiplyMat4Vec4')
c.addNode('Multiply')

c.connectSlots('ModelView.0.out1', 'MultiplyMat4Vec4.0.in2')
c.connectSlots('NormalMatrix.0.out1', 'Multiply.0.in2')
c.connectSlots('position', 'MultiplyMat4Vec4.0.in1')
c.connectSlots('normal', 'Multiply.0.in1')

c.connectSlots('eyepos', 'MultiplyMat4Vec4.0.out1')
c.connectSlots('eyenormal', 'Multiply.0.out1')
c.listCurrent()

c.writeNode("temporary/node.xml")

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
