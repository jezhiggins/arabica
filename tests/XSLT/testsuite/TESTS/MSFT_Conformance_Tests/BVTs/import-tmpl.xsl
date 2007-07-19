<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:template match="/">
        <template-1/>
        <xsl:call-template name="named"/>
        <xsl:call-template name="named-with-match"/>
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template name="named">
        <template-2/>
    </xsl:template>

    <xsl:template match="bookstore" name="named-with-match" priority="-100">
        <!-- Make sure that import precedence trumps both priority and document order -->
        <template-3/>
        <xsl:apply-templates select="book[1]"/>
    </xsl:template>

    <!-- Include stylesheet that imports other stylesheets -->
    <xsl:include href="inc/include-tmpl.inc"/>

</xsl:stylesheet>  

