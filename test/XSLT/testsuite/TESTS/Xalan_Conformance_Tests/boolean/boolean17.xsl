<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean17 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Purpose: Test of '=' operator, true value compared against a non-zero number. -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="true()=2"/>
  </out>
</xsl:template>

</xsl:stylesheet>
