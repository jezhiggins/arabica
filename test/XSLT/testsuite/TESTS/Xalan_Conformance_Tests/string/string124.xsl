<?xml version = "1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

  <!-- FileName: string124 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of contains() function searching for an entity. -->

<xsl:strip-space elements = "*"/>
<xsl:output method = "xml"/>

<xsl:template match="text()[contains(., 'SYMBOL 180 \f &quot;')]" priority="2">
   Found match of entity
</xsl:template>

<xsl:template match="*">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="text()" priority="1"/><!-- Suppress text copying if contains() fails -->

</xsl:stylesheet>
