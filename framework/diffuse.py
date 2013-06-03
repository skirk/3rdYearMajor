import Framework as fw

c = fw.Context()
'''
c.printDB()

c.addInputSlot('vert_position', VEC4)
c.addInputSlot('vert_normal', VEC4)
c.addOutputSlot('gl_Position', VEC4)
c.addOutputSlot('outColor', VEC4) 
c.addNode('toEyeCoord');
c.connectSlots('vert_position', 'toEyeCoord.0.position')
c.connectSlots('vert_normal', 'toEyeCoord.0.normal')
c.connectSlots('outColor', 'toEyeCoord.0.eyenormal')
c.connectSlots('gl_Position', 'toEyeCoord.0.eyepos')
c.writeShader('temporary/test.xml')

p = fw.processor();
p.process("test.xsl", "temporary/test.xml", "shaders/vertex.glsl");
c.listCurrent();
'''
