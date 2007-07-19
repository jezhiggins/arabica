<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: NUMBERFORMAT34 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test changing both digit and zero-digit in format string. -->

<xsl:decimal-format digit="!" zero-digit="a" />

<xsl:template match="doc">
  <out>
    <xsl:value-of select="format-number(4030201.0506,'#!!!,!!!,aaa.aaaaaa0')"/>
  </out>
</xsl:template>

</xsl:stylesheet>
