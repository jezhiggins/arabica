<?xml version="1.0"?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

  <!-- FileName: Ver02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 Stylesheet element -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Prove that transform is a synonym for stylesheet. -->

<!-- Explicitly match text nodes so the output is just 39 -->
<xsl:template match="text()">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="doc/version">
  <out>
    <xsl:value-of select="./@theattrib"/>
  </out>
</xsl:template>

</xsl:transform>