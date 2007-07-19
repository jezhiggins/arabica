<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:a="http://foo.com">

  <!-- FileName: namespace89 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test that exclude-result-prefixes should NOT affect xsl:element (when prefix needed) -->

<xsl:template match="/">
  <out xmlns:b="http://barz.com" xsl:exclude-result-prefixes="a b">
    <xsl:element name="b:mid">
      <xsl:element name="a:inner"/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>