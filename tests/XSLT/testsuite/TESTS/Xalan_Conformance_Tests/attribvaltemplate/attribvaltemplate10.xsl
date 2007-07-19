<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribvaltemplate10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Evaluation of string expression in AVT, surrounded by fixed strings. -->

<xsl:template match="doc">
  <out z="Before{concat(@a,@b)}After"/>
</xsl:template>

</xsl:stylesheet>