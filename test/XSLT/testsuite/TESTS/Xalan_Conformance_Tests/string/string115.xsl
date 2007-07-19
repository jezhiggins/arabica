<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str115 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions  -->
  <!-- Purpose: Test of 'substring()'  -->

<xsl:template match="doc">
	<out>
		<xsl:value-of select="substring('1999/04/01', 1, 0)"/>
	</out>
</xsl:template>

</xsl:stylesheet>