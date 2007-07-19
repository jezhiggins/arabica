<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH11 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.4 -->
  <!-- Purpose: Test of number() conversion function on a non-existent node. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="number(foo)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
