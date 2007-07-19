<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean82 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of '=' operator, false value compared against zero. Reverse order of boolean18. -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="0=false()"/>
  </out>
</xsl:template>

</xsl:stylesheet>
