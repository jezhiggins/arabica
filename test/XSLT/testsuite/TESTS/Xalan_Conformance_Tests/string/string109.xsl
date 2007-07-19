<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str109 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 12.3 Number Formatting  -->
  <!-- Purpose: Test of 'format-number()'  -->

<xsl:template match="doc">
	<out>
		<xsl:value-of select="format-number(1, '00.0')"/>
	</out>
</xsl:template>

</xsl:stylesheet>