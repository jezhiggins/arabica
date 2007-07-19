<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: output109 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.3 Text Output Method -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Attempt to create comment under text output method -->

<xsl:output method="text" encoding="UTF-8"/>

<xsl:template match="doc">
  <xsl:value-of select="dis"/>
  <xsl:comment>Here is my comment</xsl:comment>
  <xsl:value-of select="dat"/>
</xsl:template>

</xsl:stylesheet>
