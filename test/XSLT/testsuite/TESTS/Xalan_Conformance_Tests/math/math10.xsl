<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH10 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 3.5 -->
  <!-- Purpose: Test of 'mod' operator. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="5 mod 2"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
