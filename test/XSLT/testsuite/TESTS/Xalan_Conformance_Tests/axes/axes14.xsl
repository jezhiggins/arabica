<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES14 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Purpose: Test for ancestor-or-self::*[@att1][1]/@att1 vs. (ancestor-or-self::*)[@att1][1]/@att1. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//baz">
      <xsl:value-of select="ancestor-or-self::*[@att1][1]/@att1"/><xsl:text>, </xsl:text>
      <xsl:value-of select="(ancestor-or-self::*)[@att1][1]/@att1"/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
