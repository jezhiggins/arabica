<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo1" select="concat('foo1 pri 0 depends on: ', $foo1)"/>

    <xsl:variable name="bar1" select="concat('bar1 pri 0 depends on: ', $foo1)"/>

    <xsl:include href="inc/include-var.inc"/>

    <xsl:template match="/">
        <!-- Triangular dependency -->
        <x><xsl:value-of select="$foo1"/></x>
    </xsl:template>

</xsl:stylesheet>  

