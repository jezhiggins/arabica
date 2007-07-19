<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
		<abs-url><xsl:for-each select="document('\\webxtest\ManagedShadow\Managed_RTM\TestData\XSLT\XSLTFunctions\inc\xsl3.inc', unk)//xsl3"><xsl:copy/></xsl:for-each></abs-url>
	</xsl:template>
</xsl:stylesheet>