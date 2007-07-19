<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str22 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'substring()' function on non-existent node -->

  <xsl:template match="doc">
    <out>
      <xsl:value-of select='substring(foo, 12, 3)'/>
    </out>
  </xsl:template>
 
</xsl:stylesheet>
