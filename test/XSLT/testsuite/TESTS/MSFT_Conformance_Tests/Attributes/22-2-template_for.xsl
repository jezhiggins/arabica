<?xml version="1.0" ?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
	<xsl:apply-templates select="//item" />
	<xsl:comment>This is the end of the template section of the stylesheet</xsl:comment>
</xsl:template>

<xsl:template match="item">
	Some text in the template
</xsl:template>

</xsl:stylesheet>
