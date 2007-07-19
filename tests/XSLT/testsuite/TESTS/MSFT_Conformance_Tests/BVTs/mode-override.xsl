<!-- Regression of bug 86836 (IE database) -->
<!-- Template Manager override applied to wrong apply-templates call -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:msxsl="urn:schemas-microsoft-com:xslt" exclude-result-prefixes="msxsl">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo"><p1/></xsl:variable>

    <xsl:template match="/">
        <xsl:apply-templates select="msxsl:node-set($foo)" mode="frag-mode"/>
        <xsl:apply-templates select="bookstore"/>
    </xsl:template>

    <xsl:template match="bookstore"><hello/></xsl:template>

</xsl:stylesheet>
