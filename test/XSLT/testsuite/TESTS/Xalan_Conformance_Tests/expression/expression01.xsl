<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: expression01 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.3 -->
  <!-- Purpose: Test of lang() function, with exact match on "en" -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="para[@id='1' and lang('en')]"/>
  </out>
</xsl:template>

</xsl:stylesheet>
