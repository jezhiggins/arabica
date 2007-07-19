<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:template match="*[string(descendant::*) = concat(substring-before(//sibprec/p, 'sibling'), //child/desc/p)] | @*[string-length(self::*) != ((3 + 6 - 8) * 5)]" priority="10">
        : <xsl:element name="{name()}"/>
	<xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="*">
	<xsl:apply-templates select="* | @*"/>
    </xsl:template>

    <xsl:template match="@*"/>

    <xsl:template match="text()"/>

</xsl:stylesheet>
