<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str06 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Test of 'starts-with()'  -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="starts-with('ENCYCLOPEDIA', 'ENCY')"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
