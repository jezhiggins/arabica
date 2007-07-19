<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: Message13 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:copy inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="a">
  <xsl:message>
    <xsl:text>Message from MESSAGE13: </xsl:text>
    <xsl:copy/>
    <xsl:text>Anything between the colon and this?</xsl:text>
  </xsl:message>
</xsl:template>

</xsl:stylesheet>
