<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math103 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of unary '-' on a union. -->

<xsl:template match="doc">
  <out>
    <xsl:copy-of select="-(n1|n2)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
