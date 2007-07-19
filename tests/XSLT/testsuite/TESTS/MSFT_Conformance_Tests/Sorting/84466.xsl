<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    
      <SPAN>
       
          <xsl:for-each select="bookstore/book/author">
		<xsl:sort select="my:country"/>
		<xsl:value-of select="my:country"/>
         </xsl:for-each> 
	      
   </SPAN>
  </xsl:template>
</xsl:stylesheet>
