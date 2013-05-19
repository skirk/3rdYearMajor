import Framework as fw
from nodetype import *
from slotvariable import *

c = fw.Context()

c.printDB()

#Vertex shader
c.addInputSlot("VertexPosition", VEC3);
c.addInputSlot("VertexNormal", VEC3);
c.addOutputSlot("LightIntensity", VEC3);
c.addOutputSlot("gl_Position", VEC4);

c.addNode('ModelView');
c.addNode('ProjectionMatrix');
c.addNode('NormalMatrix');
c.addNode('Kd');
c.addNode('Ld');
c.addNode('LightPosition');



c.writeShader("temporary/shader.xml")
p = fw.processor();
p.process("graph.xsl", "temporary/shader.xml", "shaders/vertex.glsl");
