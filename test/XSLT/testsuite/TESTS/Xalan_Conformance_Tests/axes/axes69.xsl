<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: AXES69 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Compound test for preceding-sibling:: and following-sibling:: with explicit iteration. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:for-each select="preceding-sibling::*"><xsl:text>
From </xsl:text><xsl:value-of select="name(.)"/><xsl:text>:</xsl:text>
        <xsl:apply-templates select="following-sibling::*"/>
      </xsl:for-each>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:text> </xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

</xsl:stylesheet>
