<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes123 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Purpose: Tests apply-templates from an attribute using parent axis. -->
  <!-- This is a twist on axes96, where the context node is an element. -->
  <!-- Creator: David Marston -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center/@center-attr-1">
      <xsl:apply-templates select="../.."/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:value-of select="name(.)"/>
</xsl:template>

</xsl:stylesheet>