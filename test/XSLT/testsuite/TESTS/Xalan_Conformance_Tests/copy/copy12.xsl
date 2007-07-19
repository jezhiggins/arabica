<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: copy12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 1999116 -->
  <!-- Section: 11.3 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for copy-of with boolean constant -->

<xsl:template match="/">
  <out>
    <xsl:copy-of select="true()"/>
  </out>
</xsl:template>

</xsl:stylesheet>
