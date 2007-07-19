<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//Author" />
</xsl:template>	

<xsl:template match="Author">
	<xsl:element name="foo"><xsl:attribute name="bar">XXX</xsl:attribute></xsl:element>
</xsl:template>

</xsl:stylesheet>