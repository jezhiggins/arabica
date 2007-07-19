<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="foo">
		<xsl:sort select="child::elem/@a" data-type="number" /> 
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="*">
	<xsl:value-of select="@name" /> :  <xsl:value-of select="elem/@a" /> 
		<xsl:apply-templates/>  
	</xsl:template>
</xsl:stylesheet>
