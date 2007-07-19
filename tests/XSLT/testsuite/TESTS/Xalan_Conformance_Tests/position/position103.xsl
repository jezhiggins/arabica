<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position103 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: Igor Hersht -->
  <!-- Purpose: Ensure that last() takes on new value when context changes -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="item[last()-1]"/>
    <xsl:text>, </xsl:text>
    <xsl:apply-templates select="item[last()]"/>
  </out>
</xsl:template>

<xsl:template match="item">
  <xsl:value-of select="last()"/><!-- should be 1 -->
</xsl:template>

</xsl:stylesheet>