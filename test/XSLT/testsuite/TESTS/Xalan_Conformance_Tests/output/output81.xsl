<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output81 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.3 Creating Processing Instructions. -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test use of leading underscore in names of Processing instructions. -->

<xsl:template match="doc">
  <out>
    <xsl:processing-instruction name="_a_pi">foo</xsl:processing-instruction>
  </out>
</xsl:template>

</xsl:stylesheet>