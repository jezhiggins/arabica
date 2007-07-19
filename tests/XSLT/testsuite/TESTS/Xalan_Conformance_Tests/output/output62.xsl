<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP62 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 -->
  <!-- Purpose: Test for disabling output escaping in xsl:value-of on ., which has special code. HTML method. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="doc">
  <xsl:value-of select="." disable-output-escaping="yes"/>
</xsl:template>

</xsl:stylesheet>
