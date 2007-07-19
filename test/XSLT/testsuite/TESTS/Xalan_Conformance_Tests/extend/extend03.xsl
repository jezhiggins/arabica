<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: extend03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 14 Extensions -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test function-available and element-available with
     xslt elements and functions. -->

<xsl:template match="/">
<out><xsl:text>&#010;</xsl:text>
  <xsl:choose>
    <xsl:when test="element-available('xsl:value-of')">
      <xsl:text>element xsl:value-of IS defined</xsl:text>
    </xsl:when>
    <xsl:otherwise>
      <xsl:text>element xsl:value-of IS NOT defined</xsl:text>
    </xsl:otherwise>
  </xsl:choose><xsl:text>&#010;</xsl:text>

  <xsl:choose>
    <xsl:when test="function-available('document')">
      <xsl:text>function document() IS defined</xsl:text>
    </xsl:when>
    <xsl:otherwise>
      <xsl:text>function document() IS NOT defined</xsl:text>
    </xsl:otherwise>
  </xsl:choose><xsl:text>&#010;</xsl:text>

</out>
</xsl:template>

</xsl:stylesheet>
