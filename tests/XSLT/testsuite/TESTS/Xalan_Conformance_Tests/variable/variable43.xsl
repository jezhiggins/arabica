<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: variable43 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.2 -->
  <!-- AdditionalSpec: 7.5 -->
  <!-- Purpose: Test xsl:variable inside xsl:copy -->                
  <!-- Author: David Marston -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="doc">
  <xsl:copy>
    <xsl:variable name="size" select="width * depth"/>
    <xsl:element name="item">
      <xsl:value-of select="$size"/>
    </xsl:element>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>
