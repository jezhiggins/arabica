<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:import href="inc/import-override.inc"/>
    <xsl:import href="inc/import-override3.inc"/>

    <xsl:output encoding="iso-8859-1" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
        <slash/>
        <xsl:apply-imports/>
    </xsl:template>

    <xsl:template match="bookstore">
        <bookstore/>
        <xsl:apply-imports/>
    </xsl:template>

    <xsl:template match="book" mode="book-mode">
        <book/>

        <xsl:if test="true()">

            <xsl:for-each select="author">
                <xsl:for-each select=".">
                    <!-- Dummy for loops to make sure apply-imports is allowed afterwards -->
                </xsl:for-each>
            </xsl:for-each>

            <!-- Add a couple of levels between the mode-changing apply-templates and the apply-imports -->
            <xsl:apply-imports/>
        </xsl:if>
    </xsl:template>

</xsl:stylesheet>
