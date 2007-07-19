<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes109 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Purpose: Tests following axis starting from an attribute. -->
  <!-- Author: Scott Boag -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//c/@x">
      <xsl:apply-templates select="following::*"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:text> </xsl:text><xsl:value-of select="name()"/>
</xsl:template>

</xsl:stylesheet>