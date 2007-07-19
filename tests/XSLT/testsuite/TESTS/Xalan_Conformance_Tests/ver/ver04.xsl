<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

  <!-- FileName: Ver04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.1 XSLT Namespace -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for explicit specification of version attribute in stylesheet declaration above. -->

<!-- Explicitly match text nodes so the output is just 39 -->
<xsl:template match="text()">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="doc/version">
  <out>
    <xsl:value-of select="./@theattrib"/>
  </out>
</xsl:template>

</xsl:stylesheet>