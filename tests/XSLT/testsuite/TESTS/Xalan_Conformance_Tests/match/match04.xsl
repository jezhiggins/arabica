<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATCH04 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.1 -->
  <!-- Purpose: Test of node=value in predicate in match pattern. -->

<xsl:template match="letters">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="letter[.='b']">
  <xsl:value-of select="."/>
  <xsl:text> </xsl:text>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>
