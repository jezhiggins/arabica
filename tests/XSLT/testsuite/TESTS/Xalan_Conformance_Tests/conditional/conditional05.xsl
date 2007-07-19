<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test two xsl:when elements without xsl:otherwise, one succeeding. -->

<xsl:template match="doc">
  <out>
    <xsl:choose>
      <xsl:when test="blah">2</xsl:when>
      <xsl:when test="foo">1</xsl:when>
    </xsl:choose>
  </out>
</xsl:template>

</xsl:stylesheet>
