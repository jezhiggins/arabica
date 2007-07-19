<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean56 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that "and" doesn't bother with right operand if left is false -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="false() and 1 div 0"/>
  </out>
</xsl:template>

</xsl:stylesheet>
