<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for copy-of a number -->

<xsl:template match="/">
  <out>
    <xsl:copy-of select="32"/>
  </out>
</xsl:template>

</xsl:stylesheet>
