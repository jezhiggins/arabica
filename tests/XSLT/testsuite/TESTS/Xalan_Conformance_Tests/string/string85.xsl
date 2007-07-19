<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str85 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'normalize-space()' function with node. -->

<xsl:variable name="thisvalue">This       is       a       test</xsl:variable>

<xsl:template match="doc">
	<out>
		<xsl:value-of select="normalize-space(a)"/>
		<xsl:value-of select="normalize-space($thisvalue)"/>
	</out>
</xsl:template>

</xsl:stylesheet>