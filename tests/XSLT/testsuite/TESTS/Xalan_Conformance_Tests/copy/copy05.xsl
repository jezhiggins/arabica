<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: COPY05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test copy-of a string constant -->

<xsl:template match="/">
  <out>
    <xsl:copy-of select="'test'"/>
  </out>
</xsl:template>

</xsl:stylesheet>
