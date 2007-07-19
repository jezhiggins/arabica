<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template match="/">
        <ERROR/>
    </xsl:template>

    <xsl:template name="named">
        <ERROR/>
    </xsl:template>

    <xsl:template match="bookstore" name="named-with-match" priority="100">
        <ERROR/>
    </xsl:template>

    <xsl:template match="book" name="named-import">
        <ERROR/>
    </xsl:template>

</xsl:stylesheet>  

