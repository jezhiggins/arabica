<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="bookstore">
    
	<xsl:for-each select="book">
		<B><xsl:apply-templates select="author">
			<xsl:sort select="my:country"/>
		</xsl:apply-templates></B>  
	</xsl:for-each> 
</xsl:template>  

  
	  <xsl:template match="author">  
		<SPAN><xsl:value-of select="my:country"/></SPAN>
  	  </xsl:template>
</xsl:stylesheet>
