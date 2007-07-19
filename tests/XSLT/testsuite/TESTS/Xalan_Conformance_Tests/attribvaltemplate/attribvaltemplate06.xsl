<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribvaltemplate06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.2 -->
  <!-- Creator: fginestrini@3di.it -->
  <!-- Purpose: Evaluation of numeric expression in AVT, surrounded by strings. -->

<xsl:template match="response">
  <out y="before{@indice - 1}after"/>
</xsl:template>

</xsl:stylesheet>