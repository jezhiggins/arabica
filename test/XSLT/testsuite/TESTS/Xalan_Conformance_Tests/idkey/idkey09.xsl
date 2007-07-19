<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey09 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for id() behaving well when there is no DTD to designate an ID. -->

  <!-- No exception expected, but output is just some blank lines. -->

<xsl:template match="/">
<out>
  <xsl:value-of select="id('c')/@id"/>
  <xsl:apply-templates/>
</out>
</xsl:template>

</xsl:stylesheet>
