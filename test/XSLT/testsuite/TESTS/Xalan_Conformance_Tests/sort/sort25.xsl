<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="text"/>

  <!-- FileName: sort25 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Reverse the order of the nodes using an expression that is reliable. -->

<xsl:template match="/">
  <xsl:for-each select="doc/alpha">
    <xsl:sort select="count(following-sibling::*)" data-type="number"/>
    <xsl:value-of select="@key"/>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>