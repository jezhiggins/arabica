<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace17 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test indent on xsl:output with copy-of. -->

<xsl:output indent="yes"/>

<xsl:template match="/">
	<xsl:copy-of select="doc"/>
</xsl:template>

</xsl:stylesheet>
