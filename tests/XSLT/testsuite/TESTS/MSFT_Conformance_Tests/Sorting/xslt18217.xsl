<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="intlsort/Japanese">
		<xsl:sort select="日本"/>
    </xsl:apply-templates> 
</xsl:template>

<xsl:template match="Japanese">
	<xsl:value-of  select="日本"/>
</xsl:template>

</xsl:stylesheet>
