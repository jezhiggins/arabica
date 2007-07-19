<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:foo="http://www.ped.com">

  <!-- FileName: axes58 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 Axes-->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Check the attribute:: axis. The foo:doc selection is necessary
       to pick up the last doc, cuz, I change the default namespace. -->

<xsl:template match="docs">
 <out>
    <xsl:for-each select="doc">
      <xsl:apply-templates select="attribute::*"/>
    </xsl:for-each>
    <xsl:for-each select="foo:doc">
      <xsl:apply-templates select="attribute::*"/>
    </xsl:for-each>
 </out>
</xsl:template>

<xsl:template match="@*">
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>