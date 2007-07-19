<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform' >  
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>  
<xsl:template match="/">  
<D><xsl:text>&#xd;</xsl:text></D>
<A><xsl:text>&#xa;</xsl:text></A>
<DA><xsl:text>&#xd;&#xa;</xsl:text></DA>
<AD><xsl:text>&#xa;&#xd;</xsl:text></AD>
</xsl:template>  
</xsl:stylesheet>  
