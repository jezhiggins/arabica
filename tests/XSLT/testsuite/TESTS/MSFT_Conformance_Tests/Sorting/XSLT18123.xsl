<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
   
     FIRST SORT By Number:  
          <xsl:for-each select="sorttest/c|sorttest/a">
		<xsl:sort select="d|b" data-type="number" />
	        <xsl:value-of  select="."/> 
          </xsl:for-each> 
     SECOND SORT As Text:
          <xsl:for-each select="sorttest/c|sorttest/a">
		<xsl:sort select="d|b" />
	        <xsl:value-of  select="."/> 
          </xsl:for-each> 	      
  
  </xsl:template>
</xsl:stylesheet>
