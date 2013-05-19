<?xml version="1.0" encoding="utf-8"?>
<!-- multiply.xsl -->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude">
	<xsl:output method="text"/>

	<xsl:template match="/">
		<xsl:apply-templates select="root"/>
	</xsl:template>

	<xsl:template match="root">
		<xsl:apply-templates select="shader"/>
	</xsl:template>

	<xsl:template match="shader">
		<xsl:text>#version 400&#xA;</xsl:text>
		<xsl:value-of select="normalize-space()"/>
		<xsl:apply-templates select="import"/>
		<xsl:apply-templates select="export"/>
		<xsl:apply-templates select="uniforms"/>
		<xsl:apply-templates select="node[@name='root']"/>
	</xsl:template>

	<xsl:template match="node[@name='root']">

		<xsl:text>void main()&#xA;{&#xA;</xsl:text>

		<xsl:apply-templates select="node[@*]"/>

		<xsl:variable name="name" as="string" select="@name"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:for-each select="slot[@type='output']">
			<xsl:choose>
				<xsl:when test="@name='gl_Position' or @name='FragColor'">
					<xsl:value-of select="@name"/>
					<xsl:text> = </xsl:text>
					<xsl:if test="source">
						<xsl:apply-templates select="source"/>
					</xsl:if> 
				</xsl:when>
				<xsl:otherwise>
					<xsl:variable name="output" as="string" select="@name"/>
					<xsl:value-of select="concat($name, $id, $output)"/>
					<xsl:text> = </xsl:text>
					<xsl:if test="source">
						<xsl:apply-templates select="source"/>
					</xsl:if> 
				</xsl:otherwise>
			</xsl:choose>
			<xsl:text>;&#xA;</xsl:text>
		</xsl:for-each>

		<xsl:text>&#xA;}&#xA;</xsl:text>
	</xsl:template>


	<xsl:template xmlns:xsl="http://www.w3.org/1999/XSL/Transform" match="node[@name='multiply']">
		<!-- output slots -->
		<xsl:variable name="name" as="string" select="@name"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:for-each select="slot[@type='output']">
			<xsl:value-of select="@var"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="output" as="string" select="slot/@name"/>
			<xsl:value-of select="concat($name, $id, $output)"/>
			<xsl:text> = </xsl:text>
		</xsl:for-each>
		<!-- input slots -->
		<xsl:for-each select="slot[@type='input']">
			<xsl:choose>
				<xsl:when test="position() != last()">
					<xsl:choose>
						<xsl:when test="source">
							<xsl:apply-templates select="source"/>
						</xsl:when>  
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>*</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:choose>
						<xsl:when test="source"> 
							<xsl:apply-templates select="source"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>;&#xA;</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
		<xsl:apply-templates select="node"/>
	</xsl:template>

	<!--
	<xsl:template match="node[@name='state']">
		<xsl:value-of select="slot"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="slot/name"/>
		<xsl:text> = </xsl:text>
	</xsl:template>
	-->

	<xsl:template match="node[@name='Vec4Constructor']">
		<xsl:variable name="name" as="string" select="@name"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:for-each select="slot[@type='output']">
			<xsl:value-of select="@var"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="output" as="string" select="@name"/>
			<xsl:value-of select="concat($name, $id, $output)"/>
			<xsl:text> = </xsl:text>
		</xsl:for-each>
		<xsl:text>vec4</xsl:text>
		<xsl:for-each select="slot[@type='input']">
			<xsl:choose>
				<xsl:when test="position() != last()">
					<xsl:text>(</xsl:text>
					<xsl:choose>
						<xsl:when test="source">
							<xsl:apply-templates select="source"/>
						</xsl:when>  
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>,</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:choose>
						<xsl:when test="source"> 
							<xsl:apply-templates select="source"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>);&#xA;</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

	</xsl:template>

	<xsl:template match="import">
		<xsl:text>in </xsl:text>
		<xsl:apply-templates select="@type"/>
		<xsl:text> </xsl:text>
		<xsl:variable name="node" as="string" select="@parent"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:variable name="slot" as="string" select="@name"/>
		<xsl:value-of select="concat($node, $id, $slot)"/>
		<xsl:text>;&#xA;</xsl:text>
	</xsl:template>
	<xsl:template match="uniforms">
		<xsl:text>uniform </xsl:text>
		<xsl:apply-templates select="@type"/>
		<xsl:text> </xsl:text>
		<xsl:variable name="node" as="string" select="@parent"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:variable name="slot" as="string" select="@name"/>
		<xsl:value-of select="concat($node, $id, $slot)"/>
		<xsl:text>;&#xA;</xsl:text>
	</xsl:template>

	<xsl:template match="export">
		<xsl:if test="@name!='gl_Position'">
			<xsl:text>out </xsl:text>
			<xsl:apply-templates select="@type"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="node" as="string" select="@parent"/>
			<xsl:variable name="id" as="string" select="@id"/>
			<xsl:variable name="slot" as="string" select="@name"/>
			<xsl:value-of select="concat($node, $id, $slot)"/>
			<xsl:text>;&#xA;</xsl:text>
		</xsl:if>
	</xsl:template>

	<xsl:template match="source">
		<xsl:choose>
			<xsl:when test="@value">
				<xsl:value-of select="@value"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="node" as="string" select="@node"/>
				<xsl:variable name="id" as="string" select="@id"/>
				<xsl:variable name="slot" as="string" select="@slot"/>
				<xsl:value-of select="concat($node, $id, $slot)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="node[@name='dot']">
		<xsl:variable name="name" as="string" select="@name"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:for-each select="slot[@type='output']">
			<xsl:value-of select="@var"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="output" as="string" select="@name"/>
			<xsl:value-of select="concat($name, $id, $output)"/>
			<xsl:text> = </xsl:text>
		</xsl:for-each>
		<xsl:text>dot</xsl:text>
		<xsl:for-each select="slot[@type='input']">
			<xsl:choose>
				<xsl:when test="position() != last()">
					<xsl:text>(</xsl:text>
					<xsl:choose>
						<xsl:when test="source">
							<xsl:apply-templates select="source"/>
						</xsl:when>  
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>,</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:choose>
						<xsl:when test="source"> 
							<xsl:apply-templates select="source"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>);&#xA;</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

	</xsl:template>
	<xsl:template match="node[@name='max']">
		<xsl:variable name="name" as="string" select="@name"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:for-each select="slot[@type='output']">
			<xsl:value-of select="@var"/>
			<xsl:text> </xsl:text>
			<xsl:variable name="output" as="string" select="@name"/>
			<xsl:value-of select="concat($name, $id, $output)"/>
			<xsl:text> = </xsl:text>
		</xsl:for-each>
		<xsl:text>max</xsl:text>
		<xsl:for-each select="slot[@type='input']">
			<xsl:choose>
				<xsl:when test="position() != last()">
					<xsl:text>(</xsl:text>
					<xsl:choose>
						<xsl:when test="source">
							<xsl:apply-templates select="source"/>
						</xsl:when>  
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>,</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:choose>
						<xsl:when test="source"> 
							<xsl:apply-templates select="source"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:text>1</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text>);&#xA;</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

	</xsl:template>

</xsl:stylesheet>

