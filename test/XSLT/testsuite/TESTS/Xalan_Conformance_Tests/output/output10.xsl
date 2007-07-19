<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml"/>

  <!-- FileName: OUTP10 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.1 -->
  <!-- Purpose: test for disabling output escaping in a variable with xsl:value-of -->

<xsl:template match="/">
  <xsl:variable name="foo">
    <xsl:value-of select="doc/foo" disable-output-escaping="yes"/>
  </xsl:variable>
  <out>
    <xsl:copy-of select="$foo"/>
  </out>
</xsl:template>

</xsl:stylesheet>
