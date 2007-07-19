<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: impincl24 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 Overriding Template Rules -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Show that global variables are in scope in apply-imports templates. -->

<xsl:import href="fragments/i24imp.xsl"/>

<xsl:variable name="color" select="'red'" />

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="tag">
  <div style="{concat('border: solid ',$color)}">
    <xsl:apply-imports/>
  </div>
</xsl:template>

</xsl:stylesheet>