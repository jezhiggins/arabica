
<xsl:stylesheet xmlns:xsl='http://www.w3.org/1999/XSL/Transform' version="1.0">  
 <xsl:output method="xml" indent="yes"/>
<xsl:template match="/">
<top>
	<xsl:apply-templates/>
</top>
</xsl:template>

<xsl:template match="//SECTION[2]">  
                        <P><xsl:value-of/></P>  
</xsl:template>  
</xsl:stylesheet>  
