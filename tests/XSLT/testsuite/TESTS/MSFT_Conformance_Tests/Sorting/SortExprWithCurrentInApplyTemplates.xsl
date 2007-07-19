<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
             <xsl:template match="/">
                        <xsl:apply-templates select="/collection/ref">
                                    <xsl:sort select="/collection/part[@id = current()/@refid]/@type" order="ascending"/>
                        </xsl:apply-templates>
            </xsl:template>

            <xsl:template match="*">
                        <xsl:copy-of select="/collection/part[@id = current()/@refid]" />
            </xsl:template>
</xsl:stylesheet>