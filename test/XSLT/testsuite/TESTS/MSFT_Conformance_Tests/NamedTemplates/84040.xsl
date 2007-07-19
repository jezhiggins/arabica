
<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">  
 
<xsl:template match="/bookstore/*">  
	<xsl:call-template name=" " />  
	
  
	
 
</xsl:template>  
 
<xsl:template name=" " match="my:book">  
<xsl:copy/>  
<xsl:text> </xsl:text>  
</xsl:template>


</xsl:stylesheet>  

