<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable41 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.4 -->
  <!-- Purpose: Because root node is current when top-level param is set, can get top-level comment. -->
  <!-- Author: David Marston -->

<xsl:param name="z" select="comment()"/>

<xsl:template match="doc">
  <out>
    <xsl:text>$z contains</xsl:text>
    <xsl:value-of select="$z"/>
  </out>
</xsl:template>

</xsl:stylesheet>
