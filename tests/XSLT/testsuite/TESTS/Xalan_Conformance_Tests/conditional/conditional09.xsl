<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test single when with xsl:otherwise, success on when. -->

<xsl:template match="doc">
  <out>
    <xsl:choose>
      <xsl:when test="foo">1</xsl:when>
      <xsl:otherwise>2</xsl:otherwise>
    </xsl:choose>
  </out>
</xsl:template>

</xsl:stylesheet>
