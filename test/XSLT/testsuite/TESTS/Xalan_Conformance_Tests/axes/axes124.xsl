<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes123 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Purpose: Tests apply-templates from a comment using parent axis. -->
  <!-- Creator: David Marston -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center/comment()">
      <xsl:apply-templates select=".."/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="comment()">
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="text()"/><!-- suppress whitespace-only nodes -->

</xsl:stylesheet>