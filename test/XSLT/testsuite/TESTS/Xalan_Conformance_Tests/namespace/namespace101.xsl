<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns="http://testguys.com" xmlns:ped="http://www.test.com">

  <!-- FileName: namespace101 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements with xsl:element. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Use "plain" xsl:element while both default and prefixed NS defined at top. -->

<xsl:template match="doc">
  <out>
    <xsl:element name="inner"/>
  </out>
</xsl:template>

</xsl:stylesheet>
