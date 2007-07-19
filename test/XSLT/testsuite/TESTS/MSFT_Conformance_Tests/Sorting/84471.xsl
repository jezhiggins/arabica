<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
 
sort first on descending price, then on ascending title


          <xsl:for-each select="bookstore/book">
		<xsl:sort select="price" data-type="number" order="descending"/>
		<xsl:sort select="title" order="ascending"/>
<xsl:value-of  select="title"/> is a <xsl:value-of select="@style"/> priced at <xsl:value-of select="price"/> 


         </xsl:for-each> 
	      
   
  </xsl:template>
</xsl:stylesheet>
