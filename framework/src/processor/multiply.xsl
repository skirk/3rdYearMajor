<?xml version="1.0" encoding="utf-8"?>
<!-- multiply.xsl -->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="text"/>

	<xsl:template match="/">
		<xsl:text>#version 400&#xA;</xsl:text>
		<xsl:text>void main()&#xA;{&#xA;</xsl:text>
		<xsl:apply-templates select="nodes"/>
		<xsl:text>}&#xA;</xsl:text>
	</xsl:template>

	<xsl:template match="nodes">
		<xsl:apply-templates select="node[@name='multiply']"/>
		<xsl:apply-templates select="node[@name='plus']"/>
	</xsl:template>

	<xsl:template match="node[@name='multiply']">
		<xsl:apply-templates select="slot[@type='output']"/>
		<xsl:apply-templates select="inputs"/>
	</xsl:template>

	<!-- output slots -->
	<xsl:template match="slot[@type='output']">
		<xsl:value-of select="@sort"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="name"/>
		<xsl:text>=</xsl:text>
	</xsl:template>
	<!-- input slots -->
	<xsl:template match="inputs">
		<xsl:for-each select="slot">
			<xsl:if test="self::node()">
				<xsl:text>inside</xsl:text>
			</xsl:if>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="node[@name='plus']">
		<xsl:text>&#xA;</xsl:text>
	</xsl:template>
</xsl:stylesheet>
