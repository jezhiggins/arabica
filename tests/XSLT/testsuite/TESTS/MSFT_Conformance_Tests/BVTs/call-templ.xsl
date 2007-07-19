<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template name="simple-call-template">
        <simple-call-template/>
    </xsl:template>

    <xsl:template match="/">
        <xsl:call-template name="simple-call-template"/>

        <xsl:call-template name="forward-call-template"/>

        <xsl:call-template name="with-match-and-mode"/>

        <xsl:apply-templates select="bookstore" mode="foo"/>

        <xsl:call-template name="with-params">
            <!-- Comment -->
            <?my-pi?>
            <xsl:with-param name="param1" select="'string'"/>
            <xsl:with-param name="param2" select="10"/>
        </xsl:call-template>

        <xsl:call-template name="recursive-template"/>

        <!-- Should match built-in template, not a template without a match attribute -->
        <last-name><xsl:apply-templates select="/bookstore/book[1]/author/last-name"/></last-name>
    </xsl:template>

    <xsl:template name="forward-call-template">
        <forward-call-template/>
    </xsl:template>

    <xsl:template match="bookstore" priority="1" mode="foo" name="with-match-and-mode">
        <with-match-and-mode><xsl:value-of select="book/title"/></with-match-and-mode>
    </xsl:template>

    <xsl:template name="with-params">
        <xsl:param name="param1"/>
        <xsl:param name="param2"/>
        <with-params><xsl:value-of select="concat('param1: ', $param1, ', ')"/><xsl:value-of select="concat('param2: ', $param2)"/></with-params>
    </xsl:template>

    <xsl:template name="recursive-template">
        <xsl:param name="foo" select="1"/>

        <!--Regress memory leak when call-template invokes itself -->
        <recursive-template>
            <xsl:if test="$foo &lt; 2">
                <xsl:call-template name="recursive-template">
                    <xsl:with-param name="foo" select="$foo + 1"/>
                </xsl:call-template>
            </xsl:if>
        </recursive-template>
    </xsl:template>

</xsl:stylesheet>