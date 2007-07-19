<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: sort05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 10 -->
  <!-- Purpose: Test for xsl:sort on a descendant element with no order specified. -->

<xsl:template match="w3cgroup">
  <out>
    <xsl:apply-templates select="member">
      <xsl:sort select="primary/name/last"/>
      <xsl:sort select="primary/name/first"/>
    </xsl:apply-templates>
  </out>
</xsl:template>

<xsl:template match="member">
  <xsl:value-of select="primary/name/last"/><xsl:text> </xsl:text>
  <xsl:value-of select="primary/name/first"/><xsl:text>; </xsl:text>
</xsl:template>

</xsl:stylesheet>
