<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP54 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Test for creating a comment using a formula. -->

<xsl:template match="/">
  <Out>
    <xsl:comment><xsl:value-of select="substring('abcdefghi',2,4)"/></xsl:comment>
  </Out>
</xsl:template>

</xsl:stylesheet>