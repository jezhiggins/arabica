<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: node09 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 Node Tests -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for value-of with comment() node test. -->

<xsl:template match="/doc">
  <out>      
    <xsl:apply-templates select="./comment()"/>
  </out>
</xsl:template>

<xsl:template match="comment()">
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
