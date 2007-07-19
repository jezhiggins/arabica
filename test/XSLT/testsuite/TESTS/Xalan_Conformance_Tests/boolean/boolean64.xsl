<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean64 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of '!=' operator on two booleans, true first. -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="true()!=false()"/>
  </out>
</xsl:template>

</xsl:stylesheet>