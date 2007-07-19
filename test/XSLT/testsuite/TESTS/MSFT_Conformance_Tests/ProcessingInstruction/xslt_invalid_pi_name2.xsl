<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="*">
<out>
	<!-- Test case for bug 71241, ':' is not allowed in a PI. Should be ignored. -->
	<xsl:processing-instruction name="xsl:foo">
		This should not get displayed!
	</xsl:processing-instruction>	
</out>
</xsl:template>
</xsl:stylesheet>