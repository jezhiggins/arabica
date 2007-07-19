<?xml version = "1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

  <!-- FileName: string129 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of contains() function using a numbered entity. -->

<xsl:strip-space elements = "*"/>
<xsl:output method = "xml" indent = "yes"/>

<xsl:template match="doc">
  <out>
    <xsl:value-of select="contains(., '&#38;')"/>
  </out>
</xsl:template>

</xsl:stylesheet>
