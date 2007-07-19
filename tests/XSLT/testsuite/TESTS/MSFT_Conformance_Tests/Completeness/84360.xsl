<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//Author" />
</xsl:template>
<xsl:template match="*">
	<xsl:element name="fred"><xsl:attribute name="foo"><xsl:value-of select="."/>
	<xsl:for-each select="//item[photo]">-</xsl:for-each></xsl:attribute></xsl:element>
</xsl:template>
</xsl:stylesheet>