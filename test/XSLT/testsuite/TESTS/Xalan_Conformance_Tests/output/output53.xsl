<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP53 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.4 Creating Comments -->
  <!-- Purpose: Basic test for creating a comment. -->

<xsl:template match="/">
  <Out>
    <xsl:comment>This should be inserted as-is.</xsl:comment>
  </Out>
</xsl:template>

</xsl:stylesheet>