<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional11 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:if with test expression that converts to boolean true. -->

<xsl:template match="/">
  <out>
  <xsl:if test="'StringConstant'">
    <xsl:text>StringConstant</xsl:text>
  </xsl:if>
  <xsl:if test="0">
    <xsl:text>Failed</xsl:text>
  </xsl:if>
  </out>
</xsl:template>

</xsl:stylesheet>
