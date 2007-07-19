<?xml version='1.0'?>


<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:axsl="http://my.com"
    exclude-result-prefixes="axsl">

    <!-- Regression test case result for bug 71054 -->

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="no" indent="no" />

    <xsl:namespace-alias stylesheet-prefix="#default" result-prefix="axsl"/>

    <xsl:template match="/">
        <x/>
    </xsl:template>

</xsl:stylesheet>
