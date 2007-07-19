<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: SORT34 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Try to set case-order from a variable. -->

<xsl:template match="doc">
  <xsl:variable name="ord" select="'lower-first'"/>
  <out>
    <xsl:for-each select="item">
      <xsl:sort lang="en-US" case-order="{$ord}"/>
      <xsl:copy-of select="."/><xsl:text>
</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
