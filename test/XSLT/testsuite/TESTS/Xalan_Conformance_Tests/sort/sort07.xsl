<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: SORT07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Purpose: Test for xsl:sort on a different element (not always present)
       which should have tie-breakers. -->

<xsl:template match="w3cgroup">
  <out>
    <xsl:apply-templates select="member">
      <xsl:sort select="alternate/name/first" order="ascending"/>
      <xsl:sort select="alternate/name/last" order="descending"/>
    </xsl:apply-templates>
  </out>
</xsl:template>

<xsl:template match="member">
  <xsl:value-of select="affiliation"/><xsl:text>: </xsl:text>
  <xsl:value-of select="alternate/name/first"/><xsl:text> </xsl:text>
  <xsl:value-of select="alternate/name/last"/><xsl:text>
</xsl:text>
</xsl:template>

</xsl:stylesheet>
