<!-- This test case exercises handcreation of an lang or space attribute using 
QSpace xml and the xslt attribute element -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output omit-xml-declaration="yes" />

    <xsl:template match="/">
        <root>
            <xsl:attribute name="xml:space">default</xsl:attribute>
        </root>
    </xsl:template>

    <xsl:template match="text()"></xsl:template>

</xsl:stylesheet>