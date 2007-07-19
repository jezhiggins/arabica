<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy29 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.4 current() -->
  <!-- Creator: David Marston -->
  <!-- Purpose: current() should work in copy-of. -->

<xsl:template match="/">
  <out>
    <xsl:copy-of select="."/>
    <xsl:text>&#10;</xsl:text>
    <xsl:copy-of select="current()"/>
  </out>
</xsl:template>

</xsl:stylesheet>