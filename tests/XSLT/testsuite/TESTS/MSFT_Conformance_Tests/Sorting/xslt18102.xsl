<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    
      <SPAN>
       
          <xsl:for-each select="bookstore/book/author">
		
		<xsl:value-of select="last-name"/>
         </xsl:for-each> 
	      
   </SPAN>
  </xsl:template>
</xsl:stylesheet>
