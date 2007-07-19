<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output87 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16 -->
  <!-- Discretionary: two-output-same-attribute="choose-last" -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check merging of multiple declarations of xsl:output. -->

<xsl:output method="xml" encoding="US-ASCII" indent="no"
    omit-xml-declaration="yes" cdata-section-elements="a b"/>
<xsl:output method="xml" encoding="UTF-8"
    omit-xml-declaration="no" cdata-section-elements="c d"/>

<xsl:template match='/'>
  <out>
    <xsl:for-each select="doc/*">
      <xsl:text>&#10;</xsl:text>
      <xsl:copy-of select="."/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>