<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: lre09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.1 Literal Result Elements-->
  <!-- Creator: David Marston -->
  <!-- Purpose: Ensure that names are preserved, case and all. -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out AtTrib-0.01="Mix-d.Char5">Text-A<Sub-Elem2.0/>teXt.B</out>
</xsl:template>

</xsl:stylesheet>