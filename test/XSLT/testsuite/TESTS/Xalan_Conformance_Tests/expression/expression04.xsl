<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: EXPR04 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.3 -->
  <!-- Purpose: Test of lang() function -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="div/para[lang('en')]"/>
  </out>
</xsl:template>

</xsl:stylesheet>
