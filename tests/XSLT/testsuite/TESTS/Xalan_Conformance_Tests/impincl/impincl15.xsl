<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl15 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 Overriding Template Rules -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that apply-imports stays in same mode as what called it. -->

<xsl:import href="s.xsl"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates mode="yes"/>
  </out>
</xsl:template>

<xsl:template match="tag" mode="yes">
  <div style="border: solid green">
    <xsl:apply-imports/>
  </div>
</xsl:template>

<xsl:template match="tag">
  <div style="border: solid red">
    <xsl:apply-imports/>
  </div>
</xsl:template>

</xsl:stylesheet>
