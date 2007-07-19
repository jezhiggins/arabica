<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
  <HTML>
  <BODY>
  <H3>Books:</H3>
  <OL>
  <xsl:for-each select="//Book">
	<xsl:sort select="//Title" order="ascending"/>
  	<xsl:apply-templates select="*"/>
  </xsl:for-each>
  </OL>
  </BODY>
  </HTML>
</xsl:template>

<xsl:template match="Title">
	<LI><xsl:value-of select="."/></LI>
</xsl:template>

<xsl:template match="Author">
	by <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
