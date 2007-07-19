<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="utf-8" omit-xml-declaration="yes"/>

    <xsl:template match="/">

        <!-- Whitespace within xsl:choose should not be output to result tree -->
        <xsl:choose>

            <!-- Ignore this comment -->

            <?my-pi Ignore this PI ?>

            <xsl:when test="true()"><hello/></xsl:when>

            <xsl:otherwise><goodbye/></xsl:otherwise>
    
        </xsl:choose>

    </xsl:template>

</xsl:stylesheet>
