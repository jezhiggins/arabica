<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: If equal priorities are explicitly assigned, default priority
     rules have no effect on resolving conflicts. -->
  <!-- should see 1 conflict warning -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="file"/>
  </out>
</xsl:template>

<xsl:template match="file[@test='false']" priority="2">
  <xsl:text>Match-predicated-wildcard,</xsl:text>
</xsl:template>

<xsl:template match="file" priority="2">
  <xsl:text>Match-wildcard,</xsl:text>
</xsl:template>

</xsl:stylesheet>
