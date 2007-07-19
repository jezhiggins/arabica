<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo5" select="'foo5 pri -1'"/>

    <xsl:variable name="foo6" select="concat('foo6 pri -1 depends on ', $foo6)"/>

    <xsl:variable name="foo7" select="concat('foo7 pri -1 depends on ', $foo7)"/>

    <xsl:variable name="foo8" select="'foo8 pri -1'"/>

    <xsl:variable name="foo9" select="concat('foo9 pri -1 depends on ', $foo10)"/>

    <xsl:variable name="foo10" select="concat('foo10 pri -1 depends on ', $foo9)"/>

</xsl:stylesheet>
