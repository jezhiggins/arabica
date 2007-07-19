<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:template match="book">
        <xsl:value-of select="title"></xsl:value-of>
        <xsl:apply-templates><!-- This is a comment --><!--Apply Templates can have all these below but not any other nodes like plain text or text nodes--><?mypi ?> 	
<!--foo is redundant and should error out-->
foo

</xsl:apply-templates>
    </xsl:template>
    <xsl:template match="text()"></xsl:template>
</xsl:stylesheet>
