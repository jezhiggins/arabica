
<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
  <xsl:template match="/xslTutorial/*">  
	<p>  
	   <xsl:call-template name="for"/>  
	</p>  
  </xsl:template>  
 
  <xsl:template name="for" match="for">  
 
	<xsl:if test="$start">  
	   <foo/>
	</xsl:if>  

  </xsl:template>  

</xsl:stylesheet>  

