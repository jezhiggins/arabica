<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
<RESULT>
<xsl:for-each select = "data/a">
	<xsl:sort select="number(@x)"/>
	<xsl:copy><xsl:attribute name = "x" ><xsl:value-of select = "@x" /></xsl:attribute></xsl:copy>
</xsl:for-each>
</RESULT>
</xsl:template>
</xsl:stylesheet>
