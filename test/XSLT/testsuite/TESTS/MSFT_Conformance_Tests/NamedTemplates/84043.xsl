<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
<xsl:output method="xml" omit-xml-declaration="yes" />
 
<xsl:template match="/bookstore/*">  
	<xsl:call-template name="book" />  
</xsl:template>  
 
<xsl:template name="book" match="book">  
<xsl:copy/>  
<xsl:text> </xsl:text>  
</xsl:template>
<xsl:template name="foo" match="magazine">  
<xsl:copy/>  
<xsl:text> </xsl:text>  
</xsl:template>


</xsl:stylesheet>  

