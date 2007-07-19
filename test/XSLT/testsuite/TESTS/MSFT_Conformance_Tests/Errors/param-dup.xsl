<!-- Error Case -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <xsl:apply-templates select=".">
            <xsl:with-param name="xsl:foo"/>
            <xsl:with-param name="bar1"/>
            <xsl:with-param name="bar2"/>
            <xsl:with-param name="bar3"/>
            <xsl:with-param name="xsl:foo"/>
        </xsl:apply-templates>

    </xsl:template>

</xsl:stylesheet>
