<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey58 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for id($var), where $var has a string with a list of ID values. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:variable name="list" select="'z w x'"/>

<xsl:template match="/">
  <out>
    <xsl:for-each select="id($list)">
      <xsl:value-of select="."/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>