<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean62 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of '!=' operator on two numbers, one having decimal point and zeroes after -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="1 != 1.00"/>
  </out>
</xsl:template>

</xsl:stylesheet>