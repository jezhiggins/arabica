<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Purpose: Test for key() in template pattern matching. --> 

<xsl:key name="mykey" match="div" use="title"/>

<xsl:template match="doc">
 <out>
  <xsl:apply-templates select="key('mykey', 'Introduction')/p"/>
  <xsl:apply-templates select="key('mykey', 'Stylesheet Structure')"/>
  <xsl:apply-templates select="key('mykey', 'Expressions')/p"/>
  <xsl:apply-templates select="key('mykey', 'Patterns')"/>
 </out>
</xsl:template>

<xsl:template match="key('mykey', 'Introduction')/p">
  <xsl:value-of select="."/><xsl:text>,</xsl:text>
</xsl:template>

<xsl:template match="key('mykey', 'Stylesheet Structure')">
  <xsl:value-of select="p"/><xsl:text>,</xsl:text>
</xsl:template>

<xsl:template match="key('mykey', 'Expressions')/p">
  <xsl:value-of select="."/><xsl:text>,</xsl:text>
</xsl:template>

<xsl:template match="key('mykey', 'Patterns')">
  <xsl:value-of select="p"/>
</xsl:template>

</xsl:stylesheet>
