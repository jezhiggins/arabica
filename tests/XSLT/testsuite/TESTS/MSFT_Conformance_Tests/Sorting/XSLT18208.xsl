<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">    
   
<xsl:for-each select="sorttest/numbers[@dtype = 'text']">
<B><xsl:apply-templates select="no">
		<xsl:sort select="." data-type="number"/>
</xsl:apply-templates></B>  
 </xsl:for-each>
</xsl:template>  

  
	  <xsl:template match="no">  <SPAN>  
          
		<xsl:value-of select="."/> is at position <xsl:value-of select="@pos"/><br/>
	
            <br/>

          
	    
   </SPAN>
  </xsl:template>
</xsl:stylesheet>
