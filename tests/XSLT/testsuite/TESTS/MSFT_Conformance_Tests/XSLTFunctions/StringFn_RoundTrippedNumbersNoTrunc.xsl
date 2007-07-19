<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- Regression test case for bug 70777. -->

	<xsl:output encoding="UTF-8" />

	<xsl:template match="/">
		<!-- Do these two numbers reduce to the same IEEE bit pattern? -->
		<xsl:if test="number(0.047025229999999994) != number(0.04702523)">

			<!-- If they don't, so when each bit pattern is converted back to a string, the resulting strings should be different -->
			<xsl:if test="string(number(0.047025229999999994)) = string(number(0.04702523))">
				<ERROR>The processor has a roundtripping bug!!</ERROR>
			</xsl:if>
			<root>
			<left><xsl:value-of select='string(number(0.047025229999999994))'/></left>
			<right><xsl:value-of select='string(number(0.04702523))' /></right>
			</root>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
