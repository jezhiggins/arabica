<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: boolean65 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of '!=' operator on two booleans that are equal, so false should result. -->

<xsl:template match="/">
  <out>
    <xsl:value-of select="false()!=false()"/>
  </out>
</xsl:template>

</xsl:stylesheet>