<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
                xmlns:ns1="http://www.ns1.com" xmlns:ns2="http://www.ns2.com"
                exclude-result-prefixes="ns1 ns2">

  <!-- FileName: whitespace22 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 Whitespace Stripping -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Testing the applicable match for a particular element, also
       verifying that preserve-space works with namespace-prefixed element.
       This generate an error, recovering with the match that occurs last in
       the stylesheet. -->

<xsl:strip-space elements="ns1:test ns2:test"/>
<xsl:preserve-space elements="ns1:test"/>

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="*"/>
  </out>
</xsl:template>

</xsl:stylesheet>
