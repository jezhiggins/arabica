<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str44 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'starts-with()' function. -->

<xsl:template match="doc">
	<out>
		<xsl:value-of select="starts-with('ENCYCLOPEDIA', 'EN')"/>
	</out>
</xsl:template>

</xsl:stylesheet>