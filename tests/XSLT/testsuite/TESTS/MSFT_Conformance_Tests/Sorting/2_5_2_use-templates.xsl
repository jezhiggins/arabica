<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
	<xsl:apply-templates select="//Book">
		<xsl:sort select="Title" order="descending" />
	</xsl:apply-templates>
</xsl:template>	

<xsl:template match="Book">
	<hr/>
	<B>Title:</B><xsl:value-of select="Title" />
	<B>Author:</B><xsl:value-of select="Author" />
</xsl:template>

</xsl:stylesheet>