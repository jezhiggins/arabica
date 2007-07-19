<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:variable name="foo2" select="concat('foo2 pri 0 depends on: ', $foo2)"/>

    <xsl:include href="inc/include-var.inc"/>

    <xsl:template match="/">
        <!-- Two variable dependency -->
        <x><xsl:value-of select="$foo1"/></x>
    </xsl:template>

</xsl:stylesheet>  

