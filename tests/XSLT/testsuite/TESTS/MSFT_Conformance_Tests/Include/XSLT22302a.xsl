<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:param name="a" select="//book/author/lastname[1]"></xsl:param>
    <xsl:template match="/">
        <span style="color=red">
  This text is from the main stylesheet. </span>
        <p></p>
        <xsl:for-each select="//book/author">
            <span style="color=green" ID="test">
                <xsl:value-of select="award"></xsl:value-of>
            </span>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
