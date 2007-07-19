<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy30 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use key() to try to create a set of nodes in random order. -->

<xsl:key name="k" use="@origin" match="a" />

<xsl:template match="/">
  <out>
    <xsl:copy-of select="key('k','Albany')"/>
  </out>
</xsl:template>

</xsl:stylesheet>