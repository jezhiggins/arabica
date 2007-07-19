<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select03 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for select in for-each and current(). -->

<xsl:template match="doc">
  <out>
    <xsl:for-each select="foo">
      <xsl:copy-of select="//item[@type=current()/@name]"/><xsl:text> </xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
