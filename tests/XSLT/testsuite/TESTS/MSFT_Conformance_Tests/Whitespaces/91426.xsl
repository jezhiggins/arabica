<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method = "xml" encoding="UTF-8" omit-xml-declaration="yes" indent="no"/>

<xsl:preserve-space elements="strip nums treebuilder u p span table tr"/>

<xsl:variable name="ws" xml:space="default">
    <root>
        <strip>
            <text> Hello   World </text>
        </strip>
        <nums>
            <num>5</num>
            <num>2</num>
        </nums>
        <treebuilder>
            <!-- TreeBuilder calls getText -->
            <u><xsl:value-of select="html/div/p/u"/></u>
        </treebuilder>
    </root>
</xsl:variable>

<xsl:template match="/">
    <!-- Call get-text on various other node types -->
    <docfrag><xsl:value-of select="$ws"/></docfrag>
    <document><xsl:value-of select="/"/></document>
    <comment><xsl:value-of select="comment()"/></comment>
    <pi><xsl:value-of select="processing-instruction()"/></pi>
    <attribute><xsl:value-of select="html/div/@xml:space"/></attribute>
    <cdata><xsl:value-of select="html/div/span/text()"/></cdata>
    <pcdata-notws><xsl:value-of select="html/h1/text()"/></pcdata-notws>
    <pcdata-stripws><xsl:value-of select="html/div/p/text()"/></pcdata-stripws>
    <pcdata-preservews><xsl:value-of select="html/div/text()"/></pcdata-preservews>
</xsl:template>

</xsl:stylesheet>
