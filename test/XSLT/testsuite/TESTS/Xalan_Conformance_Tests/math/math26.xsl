<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH26 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.4 -->
  <!-- Purpose: Test of floor() near a boundary. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="floor(2.999999)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
