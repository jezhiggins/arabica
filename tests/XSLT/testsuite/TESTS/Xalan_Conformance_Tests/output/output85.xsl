<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output85 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Check that xml:lang is properly copied from literal attribute. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:template match='/'>
  <out xml:lang="en-US"/>
</xsl:template>

</xsl:stylesheet>