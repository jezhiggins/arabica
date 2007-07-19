<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean22 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Purpose: Test of boolean "and" operator with one value false and one value true -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="false() and true()"/><xsl:text>,</xsl:text>
  </out>
</xsl:template>

</xsl:stylesheet>
