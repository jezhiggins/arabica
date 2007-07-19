<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATH06 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 3.5 -->
  <!-- Purpose: Test of '*' operator. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="2*3"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
