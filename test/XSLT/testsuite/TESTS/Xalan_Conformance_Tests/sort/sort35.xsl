<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="text"/>

  <!-- FileName: sort35 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test the famous technique for choosing the sort key dynamically. -->

<xsl:variable name="sortcol" select="'left'"/>
<!-- Set value to either 'left' or 'right' above. Could change to external param. -->

<xsl:template match="/">
  <xsl:for-each select="doc/alpha">
    <xsl:sort select="./*[name(.) = $sortcol]" data-type="text" />
    <xsl:value-of select="concat(left,right,orig)"/><xsl:text>,</xsl:text>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>