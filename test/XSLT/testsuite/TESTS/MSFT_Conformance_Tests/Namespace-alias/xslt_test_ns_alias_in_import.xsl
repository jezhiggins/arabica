<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:myxsl="myxsl_uri" >

<xsl:import href="xslt_test_ns_alias_in_import.inc" />

<xsl:output method="xml" indent="yes" />

    <xsl:namespace-alias stylesheet-prefix="myxsl" result-prefix="xsl"/>

    <xsl:template match="/">
	<myxsl:bar/>
	<xsl:apply-imports />
    </xsl:template>

</xsl:stylesheet>