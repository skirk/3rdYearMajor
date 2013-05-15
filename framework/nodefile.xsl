<?xml version="1.0" encoding="utf-8"?>
<!-- multiply.xsl -->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude">
	<xsl:output method="text"/>

	<xsl:template match="/">
		<xsl:text>#version 400&#xA;void main()&#xA;{&#xA;</xsl:text>
		<xsl:apply-templates select="root"/>
		<xsl:text>&#xA;}&#xA;</xsl:text>
	</xsl:template>

	<xsl:template match="root">
		<xsl:apply-templates select="node"/>
	</xsl:template>

	<xsl:template match="node">
		<xsl:apply-templates select="node[@*]"/>
	</xsl:template>
	<xsl:template match="source">
		<xsl:variable name="node" as="string" select="@node"/>
		<xsl:variable name="id" as="string" select="@id"/>
		<xsl:variable name="slot" as="string" select="@slot"/>
		<xsl:value-of select="concat($node, $id, $slot)"/>
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
		<xsl:apply-templates select="node[@*]"/>
	</xsl:template>


	<xsl:template xmlns:xsl="http://www.w3.org/1999/XSL/Transform" match="node[@name='bleebluu']">
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

		<xsl:apply-templates select="node[@*]"/>
	</xsl:template>
	<xsl:template match="node[@name='state']">
		<xsl:value-of select="slot"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="slot/name"/>
		<xsl:text> = </xsl:text>
	</xsl:template>

</xsl:stylesheet>

