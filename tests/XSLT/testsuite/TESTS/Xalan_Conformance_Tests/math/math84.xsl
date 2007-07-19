<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: math84 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.4 Number Functions-->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of sum(). -->

<xsl:template match="doc">
  <out><xsl:text>&#10;</xsl:text>
    <xsl:variable name="rtf" select="av//h"/>
	<xsl:copy-of select="$rtf"/><xsl:text>&#10;</xsl:text>
    <xsl:value-of select="sum($rtf)"/><xsl:text>&#10;</xsl:text>
	<xsl:value-of select="$rtf"/><xsl:text>&#10;</xsl:text>
  </out>

</xsl:template>

</xsl:stylesheet>
