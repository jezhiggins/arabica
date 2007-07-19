<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <non-terminating-message-1>
            <xsl:message terminate="no">
                <x/>
                <xsl:copy/>
            </xsl:message>
        </non-terminating-message-1>

        <non-terminating-message-2>
            <xsl:message>
                <x/>
                <xsl:copy/>
            </xsl:message>
        </non-terminating-message-2>

        <terminating-message attr="">
            <xsl:message terminate="yes">
                <x/>
                <xsl:message terminate="yes">
                    <xsl:value-of select="//author"/>
                </xsl:message>
            </xsl:message>
        </terminating-message>

    </xsl:template>

</xsl:stylesheet>
