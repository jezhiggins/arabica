<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES50 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for 'descendant::*' followed by 'child::*' (i.e., all grandchildren and below). -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="descendant::*/child::*"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:value-of select="name(.)"/><xsl:text> </xsl:text>
</xsl:template>

</xsl:stylesheet>
