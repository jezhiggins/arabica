<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="text"/>

  <!-- FileName: sort22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for xsl:sort using a string function for the select. -->

<xsl:template match="/">
  <xsl:for-each select="doc/alpha">
    <xsl:sort select="substring(@key,2,1)" data-type="text" />
    <xsl:value-of select="@key"/><xsl:text>,</xsl:text>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>