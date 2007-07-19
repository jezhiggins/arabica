<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position104 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: Igor Hersht -->
  <!-- Purpose: Try double positional predicates to ensure they at least raise no error -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="item[last()][last()]"/>
    <xsl:text>, </xsl:text>
    <xsl:apply-templates select="item[1][last()]"/>
  </out>
</xsl:template>

<xsl:template match="item">
  <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>