<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
<xsl:for-each select="//*">
<xsl:choose>
	<xsl:when test="name()='item'"/>
	<xsl:when test="name()='Author'">
		<xsl:apply-templates select="." />
	</xsl:when>
	<xsl:otherwise/>
</xsl:choose>
</xsl:for-each>
</xsl:template>

<xsl:template match="Author">GotMe</xsl:template>

<xsl:template match="poo">This should never happen</xsl:template>

</xsl:stylesheet>