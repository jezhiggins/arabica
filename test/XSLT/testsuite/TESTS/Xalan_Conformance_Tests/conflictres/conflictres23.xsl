<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conflictres23 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.5 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for conflict resolution on processing-instruction() node test. -->
  <!-- should see 1 conflict warning, because presence of a predicate raises priority to 0.5 -->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="processing-instruction('b-pi')[.='junk']">
  <xsl:text>PI-by-name-and-content:</xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

<xsl:template match="processing-instruction()">
  <xsl:text>Any-PI:</xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

<xsl:template match="processing-instruction()[.='junk']">
  <xsl:text>PI-by-content:</xsl:text><xsl:value-of select="name(.)"/>
</xsl:template>

<xsl:template match="processing-instruction('b-pi')">
  <xsl:text>PI-named-b:</xsl:text><xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
