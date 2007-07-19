<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output88 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check effect of import precedence on merging of xsl:output. -->

<xsl:import href="impo88.xsl"/>

<xsl:output method="xml" encoding="UTF-8"
    omit-xml-declaration="no" cdata-section-elements="c d"/>

<xsl:template match='/'>
  <out>
    <xsl:copy-of select="doc"/>
  </out>
</xsl:template>

</xsl:stylesheet>