<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <xsl:choose>
            <xsl:when test="foo">{{FOO Element}}</xsl:when>
            <xsl:otherwise>NO FOO Element Found</xsl:otherwise>
        </xsl:choose>
    </xsl:template>
</xsl:stylesheet>
