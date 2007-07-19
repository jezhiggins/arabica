<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xslalias="alias-namespace" version="1.0">

	<!-- This stylesheet is a regression test case for bug 65525. It regresses the use
 	     of the namespace-alias to output a result document that uses the namespace
	     xsl (the result-prefix) -->

	<xsl:output omit-xml-declaration="yes" />

	<xsl:namespace-alias stylesheet-prefix="xslalias" result-prefix="xsl" />

	<xsl:template match="/">
		<xsl:if test="true()">
			<xslalias:apply-templates select="item" />
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
