<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Purpose: Test for copy-of whole tree via wildcard pattern -->
  <!-- Creator: Paul Dick -->
  <!-- This test also checks handling of attributes by copy-of. -->

<xsl:template match="/">
  <out>
    <xsl:copy-of select="*"/>
  </out>
</xsl:template>

</xsl:stylesheet>
