<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Purpose: Test two xsl:when, no xsl:otherwise, second matches. -->
  <!-- Creator: David Marston -->

<xsl:template match="doc">
  <out>
    <xsl:choose>
      <xsl:when test="yada">1</xsl:when>
      <xsl:when test="blah">2</xsl:when>
    </xsl:choose>
  </out>
</xsl:template>

</xsl:stylesheet>
