<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable15 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 -->
  <!-- Purpose: Test for-each inside xsl:variable -->
  <!-- Author: David Marston -->

<xsl:template match="docs">
  <out>
    <xsl:variable name="all">
      <xsl:for-each select="a">
        <xsl:value-of select="."/>
      </xsl:for-each>
    </xsl:variable>
    <xsl:text>$all contains </xsl:text>
    <xsl:value-of select="$all"/>
  </out>
</xsl:template>

</xsl:stylesheet>
