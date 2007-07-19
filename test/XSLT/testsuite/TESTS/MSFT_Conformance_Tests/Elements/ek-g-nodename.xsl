<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//item[photo]/*" />
</xsl:template>

<xsl:template match="common">
	<xsl:element name="{name()}"><a><?pi ?><b/></a></xsl:element>
</xsl:template>

</xsl:stylesheet>