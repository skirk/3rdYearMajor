<?xml version="1.0"?>
<!-- greeting.xsl -->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="text"/>

	<xsl:template match="/">
		#include&lt;cstdlib&gt;
		#include&lt;iostream&gt;

		int main()
		{
		<xsl:apply-templates select="greeting"/>
		return EXIT_SUCCESS;
		}
	</xsl:template>

	<xsl:template match="greeting">
		<xsl:text>std::cout&lt;&lt;"</xsl:text>
		<xsl:value-of select="normalize-space()"/>
		<xsl:text>"&lt;&lt;std::endl;</xsl:text>
	</xsl:template>
</xsl:stylesheet>
