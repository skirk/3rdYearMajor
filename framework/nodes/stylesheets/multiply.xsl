<?xml version="1.0" encoding="utf-8"?>
<!-- multiply.xsl -->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="text"/>
	<xsl:template match="/">
		<xsl:text>#version 400</xsl:text>
		<xsl:text>void main(){</xsl:text>
		<xsl:apply-templates select="nodes"/>
		<xsl:text>}&#xA;</xsl:text>
	</xsl:template>


	<xsl:template match="nodes">
		<xsl:apply-templates select="node[@name='multiply']"/>
		<xsl:apply-templates select="node[@name='plus']"/>
	</xsl:template>

	<xsl:template match="node[@name='multiply']">
		<!-- output slots -->
		<xsl:for-each select="outputs">
			<xsl:value-of select="slot/@sort"/>
			<xsl:text> </xsl:text>
			<xsl:value-of select="slot/name"/>
			<xsl:text> = </xsl:text>
		</xsl:for-each>
		<!-- input slots -->
		<xsl:for-each select="inputs">
			<xsl:for-each select="slot">
				<xsl:choose>
					<xsl:when test="position() != last()">
						<xsl:value-of select="name"/>
						<xsl:text>*</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="name"/>
						<xsl:text>;</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:for-each>
		</xsl:for-each>

	</xsl:template>
	<xsl:template match="node[@name='plus']">
		<xsl:text>&#xA;</xsl:text>
	</xsl:template>
</xsl:stylesheet>
