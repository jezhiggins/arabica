<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: DFLT01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.8 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test for built-in template rule for attributes.-->

<xsl:template match="doc">
  <out>
    <xsl:apply-templates select="@test"/>
  </out>
</xsl:template>

</xsl:stylesheet>
