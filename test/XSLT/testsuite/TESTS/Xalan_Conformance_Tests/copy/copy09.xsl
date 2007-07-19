<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for xsl:copy-of with nodeset. Shows handling of namespaces. -->                

<xsl:output indent="yes"/>

<xsl:template match="/">
  <root>
    <xsl:apply-templates/>
  </root>
</xsl:template>

<xsl:template match="*">
  <xsl:copy-of select="*|@*"/>
</xsl:template>

</xsl:stylesheet>
