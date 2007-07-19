<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo1" select="concat('foo1 pri -1 depends on: ', $bar1)"/>

    <xsl:variable name="bar1" select="'bar1 pri -1'"/>

    <xsl:variable name="foo2" select="concat('foo2 pri -1 depends on: ', $foo2)"/>

</xsl:stylesheet>
