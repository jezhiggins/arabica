<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//elem">
		<xsl:sort select="ancestor::*[fruit/@name]" order="ascending"/>
		<xsl:sort select="@a" order="ascending"/>
	</xsl:apply-templates>	
</xsl:template>
	
<xsl:template match="elem">
	<xsl:value-of select="../@name"/>;
</xsl:template>

</xsl:stylesheet>
