<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean81 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of '=' operator with one number with leading zero, one not. Reverse order of boolean14.-->

<xsl:template match="/">
  <out>
    <xsl:value-of select="'001' = 1"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
