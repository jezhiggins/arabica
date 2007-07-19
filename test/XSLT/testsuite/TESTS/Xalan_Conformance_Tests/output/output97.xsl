<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

  <!-- FileName: OUTPUT97 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test effect of cdata-section-elements on xsl:copy, with descendants in tree. -->

<xsl:output method="xml" cdata-section-elements="out" encoding="UTF-8"/>

<xsl:template match="/">
  <xsl:copy-of select="*"/>
</xsl:template>

</xsl:stylesheet>