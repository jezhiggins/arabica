<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH75 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 3.5 -->
  <!-- Purpose: Test of 'div' operator with -0 as divisor. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="1 div -0 = 2 div -0"/>
  </out>
</xsl:template>

</xsl:stylesheet>
