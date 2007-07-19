<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output omit-xml-declaration="yes" />

	<xsl:template match="/">
		<xsl:call-template name="foo&#x043;"/>
	</xsl:template>

	<xsl:template name="foo&#x043;">
		Test Data
	</xsl:template>

</xsl:stylesheet>