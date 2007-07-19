<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres34 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Confirm default priority of 0 for processing-instruction('name') pattern. -->
  <!-- should see no conflict warnings -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="processing-instruction()" priority="-0.1">
  <xsl:text>Any-PI:</xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

<xsl:template match="processing-instruction()[.='junk']" priority="0.1">
  <xsl:text>PI-by-content:</xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

<xsl:template match="processing-instruction('b-pi')">
  <xsl:text>PI-named-b:</xsl:text><xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
