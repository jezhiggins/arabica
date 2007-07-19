<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.4 Miscellaneous Additional Functions. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of 'generate-id()' - ensure same node generates same ID. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="generate-id(a)=generate-id(a)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
