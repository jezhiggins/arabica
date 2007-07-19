<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a regression test case for bug 65666. It validates
	     that the base URI of a parent stylesheet that includes another - does not
             become the base uri of the included stylesheet. -->

	<xsl:template match="/">
		<xsl:apply-templates />
	</xsl:template>

	<xsl:include href="TestInc/xslt_include_TestIncBaseUri.xsl" />

</xsl:stylesheet>