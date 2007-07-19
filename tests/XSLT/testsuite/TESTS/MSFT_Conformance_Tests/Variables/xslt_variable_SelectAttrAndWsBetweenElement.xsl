<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  

<!-- This is a regression for bug 59293. The variable 'start' is assigned to a value
of empty whitespace, and has a select attribute. The XSL transformer should not generate
an error because white space is present between the variable element's start and 
close tags -->
 
	<xsl:template match="/root/*">  
	  <p>  
	    <xsl:call-template name="for"/>  
	  </p>  
	</xsl:template>  
 
	<xsl:template name="for" match="for">  
	  <xsl:variable name="start" select="1">  </xsl:variable> 
	  <xsl:if test="$start">  
	    <foo />
	  </xsl:if>
	</xsl:template>  

</xsl:stylesheet>  

