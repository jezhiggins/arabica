<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test strip-space on list of specified elements. -->

<xsl:strip-space elements="test1 test2"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="*"/>
  </out>
</xsl:template>

</xsl:stylesheet>
