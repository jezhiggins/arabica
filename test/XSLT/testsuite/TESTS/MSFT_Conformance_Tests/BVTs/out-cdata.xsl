<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my-ns="http://my.com">

    <xsl:template name="nested-elements">
        <xsl:param name="nested-level" select="1"/>

        <foo>
            <xsl:text>cdata</xsl:text>
            <foobar>
                <xsl:text>nocdata&#10;</xsl:text>
                <xsl:if test="$nested-level &lt; 20">
                    <xsl:call-template name="nested-elements">
                        <xsl:with-param name="nested-level" select="$nested-level + 1"/>
                    </xsl:call-template>
                </xsl:if>
                <xsl:text>&#10;nocdata</xsl:text>
            </foobar>
            <xsl:text>cdata</xsl:text>
        </foo>
    </xsl:template>

    <xsl:output method="xml" indent="yes"/>
    <xsl:output cdata-section-elements="" encoding="UTF-8"/>
    <xsl:output cdata-section-elements="  foo   my-ns:foo   "/>

    <xsl:output cdata-section-elements="foo" xmlns="http://default"/>
    <xsl:output cdata-section-elements="my-ns:foo" xmlns:my-ns="http://changed"/>

    <xsl:template match="/">

        <xsl:call-template name="nested-elements"/>

        <!-- Check effect of namespaces (default and otherwise) -->
        <foo>cdata</foo>
        <foo xmlns="http://default">cdata</foo>
        <foo xmlns="unknown">no-cdata</foo>
        <foobar>no-cdata</foobar>

        <my-ns:foo>cdata</my-ns:foo>
        <ns:foo xmlns:ns="http://changed">cdata</ns:foo>
        <ns:foo xmlns:ns="unknown">no-cdata</ns:foo>

        <!-- -->
        <foo>
            cdata
            <xsl:value-of select="'more-cdata'"/>
            <xsl:processing-instruction name="my-pi"/>
            cdata
            <xsl:comment/>
            cdata
            <foobar>
                no-cdata
                <foo>cdata</foo>
                no-cdata
            </foobar>
            cdata
        </foo>

    </xsl:template>

</xsl:stylesheet>
