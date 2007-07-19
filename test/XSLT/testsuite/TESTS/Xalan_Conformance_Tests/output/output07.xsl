<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml"/>

  <!-- FileName: OUTP07 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disable Output Escaping -->
  <!-- Purpose: Test for enabling output escaping in xsl:value-of, 
       XML output -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="doc/foo" disable-output-escaping="no"/>
  </out>
</xsl:template>

</xsl:stylesheet>
