<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribvaltemplate12 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.6.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Double braces to neutralize AVT processing, including colon. -->

<xsl:template match="doc">
  <out style="{{font:helvetica}}"/>
</xsl:template>

</xsl:stylesheet>