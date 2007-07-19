<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP55 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Test creating a comment from a path expression. -->

<xsl:template match="docs">
  <Out>
    <xsl:comment><xsl:value-of select="@attr"/></xsl:comment>
  </Out>
</xsl:template>

</xsl:stylesheet>