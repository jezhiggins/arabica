<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
  <HTML>
  <BODY>
  <H3>Books:</H3>
  <OL>
  <xsl:apply-templates select="//Book">
		<xsl:sort select="Title" order="descending"/>		
  </xsl:apply-templates>
  </OL>
  </BODY>
  </HTML>
</xsl:template>

<xsl:template match="Book">
		<hr/>
		<B>Title </B> <xsl:value-of select="Title" />
		<B> Author </B> <xsl:value-of select="Author" />
		<hr/>
</xsl:template>

</xsl:stylesheet>