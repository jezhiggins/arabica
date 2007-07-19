<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey37 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test id(list) filtered by a predicate, in a match pattern. -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="tee/s">
      <xsl:apply-templates select="r"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="id('b d c')/*[@size &gt; 17]" priority="2">
  <xsl:text>&#10;</xsl:text>
  <big><xsl:value-of select="../@id"/></big>
</xsl:template>

<xsl:template match="r" priority="1">
  <xsl:text>&#10;</xsl:text>
  <other><xsl:value-of select="../@id"/></other>
</xsl:template>

</xsl:stylesheet>
