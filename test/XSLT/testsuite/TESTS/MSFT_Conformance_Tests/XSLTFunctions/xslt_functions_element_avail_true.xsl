<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Purpose: Test element-available( ) function. Should return FALSE for attribute-set. -->

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="no" indent="yes"/>

    <xsl:template match="/">
    <out>
        <xsl:value-of select="element-available('apply-templates')" xmlns="http://www.w3.org/1999/XSL/Transform"/> 
    </out>
    </xsl:template>

</xsl:stylesheet>