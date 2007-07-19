<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:myxsl="temp_namespace">

    <xsl:namespace-alias stylesheet-prefix="myxsl" result-prefix="xsl"/>

    <xsl:template match="/">
	<myxsl:bar/>
	<xsl:call-template name="foo"/>
    </xsl:template>

    <xsl:template name="foo">
	<myxsl:foo/>
    </xsl:template>
</xsl:stylesheet>