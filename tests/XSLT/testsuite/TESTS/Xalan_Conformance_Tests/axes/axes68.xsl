<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes68 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 Axes-->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check that namespace axis includes all namespaces in scope. -->

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:element name="{name(.)}">
     <xsl:for-each select="namespace::*">
		<xsl:sort select="name(.)"/>
        <xsl:element name="{name(.)}"><xsl:value-of select="."/></xsl:element>
     </xsl:for-each>
  </xsl:element>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
