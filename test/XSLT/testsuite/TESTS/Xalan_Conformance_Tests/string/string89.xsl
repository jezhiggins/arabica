<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: str89 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19990922 -->
  <!-- Section: 4.2 String Functions -->
  <!-- Purpose: Test of 'translate()' function. -->

<xsl:template match="doc">
	<out>
		<xsl:value-of select="translate(&#34;BAR&#34;,&#34;Rab&#34;,&#34;TxX&#34;)"/><xsl:text>,</xsl:text>
		<xsl:value-of select='translate("B&#039;B","&#039;","&#096;")'/>
	</out>
</xsl:template>

</xsl:stylesheet>