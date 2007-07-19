<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test wildcard on strip-space overridden by preserve-space for one element. -->

<xsl:strip-space elements="*"/>
<xsl:preserve-space elements="test2"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="*"/>
  </out>
</xsl:template>

</xsl:stylesheet>
