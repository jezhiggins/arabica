<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//Author" />
</xsl:template>

<xsl:template match="Author">
	<xsl:value-of select=".">XXX</xsl:value-of>
</xsl:template>

</xsl:stylesheet>