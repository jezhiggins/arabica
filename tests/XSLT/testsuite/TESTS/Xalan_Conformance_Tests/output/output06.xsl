<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml"/>

  <!-- FileName: OUTP06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.1 -->
  <!-- Purpose: Test for disabling output escaping in xsl:value-of -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="doc/foo" disable-output-escaping="yes"/>
  </out>
</xsl:template>

</xsl:stylesheet>
