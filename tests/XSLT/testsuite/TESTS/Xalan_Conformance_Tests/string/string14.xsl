<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: string14 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of string() conversion on a variable containing a node-set -->

<xsl:template match="/">
  <xsl:variable name="which" select="doc/av//*"/>
  <out>
    <xsl:value-of select="string($which)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
