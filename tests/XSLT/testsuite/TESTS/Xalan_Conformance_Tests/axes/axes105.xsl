<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: axes105 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.2 -->
  <!-- Purpose: Tests apply-templates starting with a attribute axes
       followed by additional relative-location-path steps. -->
  <!-- Author: Paul Dick -->

<xsl:template match="/">
  <out>
    <xsl:for-each select="//center">
      <xsl:apply-templates select="@*/ancestor::*/near-north/*[4]/@*/preceding::text()"/>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="text()">
  <xsl:value-of select="' #text'"/>
</xsl:template>

</xsl:stylesheet>
