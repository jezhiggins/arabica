<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:for-each select="//elem"> 
		<xsl:sort select="ancestor::*[fruit/@name]" order="ascending"/>
		<xsl:sort select="@a" order="ascending"/>		
		<xsl:value-of select="../@name"/>;
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>