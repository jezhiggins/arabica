<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <!-- Write out different node types to result tree fragment -->
    <xsl:variable name="foo">
        <elem attr="attrText" attr2="attrText">
            <?xml-stylesheet piText?>
            <xsl:comment>commentText</xsl:comment>
            <![CDATA[ CDATA Text ]]>
            <sub-elem>
                <!-- Append chunks of text together to form text of element -->
                <xsl:for-each select=".//author">Chunk</xsl:for-each>
            </sub-elem>
        </elem>
    </xsl:variable>

    <xsl:template match="/">
        <xsl:copy-of select="$foo"/>
    </xsl:template>

</xsl:stylesheet>
