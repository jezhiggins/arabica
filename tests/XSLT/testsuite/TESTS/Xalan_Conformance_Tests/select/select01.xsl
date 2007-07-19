<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select01 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for absolute path selection.-->

<xsl:template match="/">
  <out>
    <xsl:for-each select="doc/c/d/e">
      <xsl:value-of select="/doc/a/b/@attr"/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
