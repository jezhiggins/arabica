<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output84 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check that xml:lang is properly emitted in XML output. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match='/'>
  <out>
    <xsl:attribute name="xml:lang">en-US</xsl:attribute>
  </out>
</xsl:template>

</xsl:stylesheet>