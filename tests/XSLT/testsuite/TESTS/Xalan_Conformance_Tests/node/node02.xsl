<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: node02 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.3 Node Tests -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for comment() node test. -->

<xsl:template match="/doc">
  <out>      
    <xsl:apply-templates select="./comment()"/>
  </out>
</xsl:template>

<xsl:template match="comment()">
  <xsl:text>Found-comment</xsl:text>
  <xsl:copy/>
</xsl:template>

</xsl:stylesheet>
