<?xml version="1.0" encoding="ISO-8859-1" standalone="no"?>
<!DOCTYPE HTMLlat1 SYSTEM "htmllat1.dtd">
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

  <!-- FileName: string130 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of contains() function using a numbered entity. -->

<xsl:output method="html"/>
<xsl:strip-space elements = "*"/>

<xsl:template match="doc">
  <HTML>
    <xsl:value-of select="contains(., '&deg;')"/>
  </HTML>
</xsl:template>

</xsl:stylesheet>
