<!-- xsl1.inc -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<!-- Include URL that is relative to this document's URL -->
	<xsl:include href="../xsl2.inc"/>
	<xsl:template match="book">
		<xsl1><xsl:apply-templates/></xsl1>
	</xsl:template>
</xsl:stylesheet>
