<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo1" select="'foo1 pri -2'"/>

    <xsl:variable name="foo3" select="'foo3 pri -2'"/>

    <xsl:variable name="foo6" select="'foo6 pri -2'"/>

    <xsl:include href="include-var2.inc"/>

    <xsl:variable name="foo2" select="'foo2 pri -2'"/>

    <xsl:variable name="foo4" select="'foo4 pri -2'"/>

    <xsl:variable name="foo5" select="'foo5 pri -2'"/>

    <xsl:variable name="foo7" select="'foo7 pri -2'"/>

    <xsl:variable name="loop" select="10"/>

</xsl:stylesheet>
