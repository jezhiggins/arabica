<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select68 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that document('') refers to this stylesheet, and exploit
     that fact to have data file select which template to use. -->

<xsl:template match="/document-element">
  <xsl:variable name="whichtmplt" select="chooser"/>
  <out>
    <xsl:apply-templates select="document('')/*/xsl:template[@name=$whichtmplt]"/>
  </out>
</xsl:template>

<xsl:template name="this" match="xsl:template">This template.
  <xsl:apply-templates select="document('select68.xml')//inside" mode="thismode"/>
</xsl:template>

<xsl:template name="that" match="xsl:template">That template.
  <xsl:apply-templates select="document('select68.xml')//inside" mode="thatmode"/>
</xsl:template>

<xsl:template match="inside" mode="thismode">We are inside.
  <xsl:value-of select="@xx"/>
</xsl:template>

<xsl:template match="inside" mode="thatmode">We got inside.
  <xsl:value-of select="@flag"/>
</xsl:template>

<xsl:template match="inside">We got inside, but modeless.
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template name="the_other" match="*">We are generic.
  <xsl:value-of select="name(.)"/>
</xsl:template>

</xsl:stylesheet>
