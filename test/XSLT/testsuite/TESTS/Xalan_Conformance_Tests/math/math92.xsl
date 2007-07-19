<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math92 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that NaN propagates through div. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="2 div number('xxx')"/><xsl:text>,</xsl:text>
    <xsl:value-of select="number('xxx') div 3"/>
  </out>
</xsl:template>

</xsl:stylesheet>
