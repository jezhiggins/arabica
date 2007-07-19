<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str08 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Test of 'substring-before()'  -->

<xsl:template match="/">
  <out>
     <xsl:value-of select="substring-before('1999/04/01', '/')"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
