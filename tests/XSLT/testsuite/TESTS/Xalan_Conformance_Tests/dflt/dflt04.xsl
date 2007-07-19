<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml"/>

  <!-- FileName: DFLT04 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.8 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of built-in template for elements for a named mode. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates mode="good"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="text()"><!-- Should never trigger -->
  <xsl:value-of select="translate(.,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
</xsl:template>

<xsl:template match="*"><!-- Should never trigger -->
  <xsl:text>Reverted on: </xsl:text><xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>