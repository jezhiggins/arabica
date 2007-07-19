<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output113 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.3 Text Output Method -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Attempt to create processing instruction under text output method -->

<xsl:output method="text" encoding="UTF-8"/>

<xsl:template match="doc">
  <xsl:value-of select="dis"/>
  <xsl:processing-instruction name="bogus">Here is my PI</xsl:processing-instruction>
  <xsl:value-of select="dat"/>
</xsl:template>

</xsl:stylesheet>
