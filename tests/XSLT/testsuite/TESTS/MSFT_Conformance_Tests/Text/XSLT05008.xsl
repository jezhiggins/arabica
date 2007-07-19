<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="/">
        <test>
            <xsl:attribute name="test">
                <xsl:text disable-output-escaping="yes">&amp;&lt;&quot;&gt;&apos;</xsl:text>
            </xsl:attribute>
        </test>
    </xsl:template>
</xsl:stylesheet>
