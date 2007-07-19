<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH20 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.4 -->
  <!-- Purpose: Test of number() conversion of boolean constant false. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="number(false())=0"/>
  </out>
</xsl:template>

</xsl:stylesheet>
