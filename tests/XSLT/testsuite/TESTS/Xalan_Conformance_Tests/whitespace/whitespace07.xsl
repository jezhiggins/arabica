<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
                xmlns:ns1="http://ns1">

  <!-- FileName: whitespace07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for element specifier that is a wildcard but qualified by a namespace. -->

<xsl:strip-space elements="ns1:*"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="*"/>
  </out>
</xsl:template>

</xsl:stylesheet>
