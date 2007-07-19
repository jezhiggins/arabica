<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str05 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Test of 'string()' conversion w/ element node  -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="string(doc)"/>
  </out>
</xsl:template>
 
</xsl:stylesheet>
