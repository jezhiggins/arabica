<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
      xmlns:ped="http://www.ped.com" 
      exclude-result-prefixes="ped">

  <!-- FileName: attribset20 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for selecting attributes with xml namespace prefix. -->

<xsl:template match="/docs">
  <out>
    <xsl:for-each select="doc">
      <xsl:apply-templates/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="*">
	  <xsl:value-of select="@ped:att1"/>
	  <xsl:value-of select="@xml:att1"/>
</xsl:template>

</xsl:stylesheet>
