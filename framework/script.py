import Framework as fw
from nodetype import *
from slotvariable import *

c = fw.Context()

c.printDB()

#Vertex shader
c.addInputSlot("VertexPosition", VEC3);
c.addInputSlot("VertexColor", VEC3);
c.addOutputSlot("Color", VEC4);
c.addOutputSlot("gl_Position", VEC4);

c.addNode('Vec4Constructor');
c.addNode('constfloat');

c.connectSlots("VertexPosition", "Vec4Constructor.0.in1")
c.connectSlots("constfloat.0.out1", "Vec4Constructor.0.in2")
c.connectSlots("Vec4Constructor.0.out1", "gl_Position")
c.connectSlots("VertexColor", "Color")

#Another Context for the fragment shader
c1 = fw.Context()

c1.addInputSlot("Color", VEC3);
c1.addOutputSlot("FragColor", VEC4);

c1.addNode('Vec4Constructor')
c1.addNode('constfloat')

c1.connectSlots("Color", "Vec4Constructor.0.in1")
c1.connectSlots("constfloat.0.out1", "Vec4Constructor.0.in2")

c1.connectSlots("Vec4Constructor.0.out1", "FragColor")

#c.disconnectSlots("Color")
#c.addOutputSlot("Color", VEC3);
#
#c.addNode('toEyeCoord');
#c.goDownALevel("toEyeCoord.0")
#c.addInputSlot("inPosition", VEC4);
#c.addInputSlot("inNormal", VEC4);
#c.addOutputSlot("eyeNorm", VEC4);
#c.addOutputSlot("eyePos", VEC4);
#
#c.addNode('multiplyMat4Vec3');
#c.addNode('inverseTranspose');
c.writeShader("shader.xml")
c1.writeShader("shader2.xml")
p = fw.processor();
p.process("graph.xsl", "shader.xml", "vertex.glsl");
p.process("graph.xsl", "shader2.xml", "fragment.glsl");
