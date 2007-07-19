<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:alias="http://alias">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:namespace-alias stylesheet-prefix="alias" result-prefix="alias"/>

    <!-- Override previous namespace-alias declaration -->
    <xsl:namespace-alias stylesheet-prefix="alias" result-prefix="xsl"/>

    <!-- Import namespace-alias declaration that should not override previous declarations -->
    <xsl:include href="inc/include-nsalias.inc"/>

    <xsl:template match="/">
        <alias:stylesheet alias:version="1.0"/>
    </xsl:template>

</xsl:stylesheet>
