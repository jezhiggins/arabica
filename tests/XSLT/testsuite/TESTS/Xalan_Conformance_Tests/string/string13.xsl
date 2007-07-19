<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str13 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'format-number()' function. -->

<xsl:template match="/">
  <out>
     <xsl:value-of select="format-number(1, '#,##0')"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
