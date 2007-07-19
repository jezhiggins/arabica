<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math96 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of sum() with unary - in some nodes. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="sum(e)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
