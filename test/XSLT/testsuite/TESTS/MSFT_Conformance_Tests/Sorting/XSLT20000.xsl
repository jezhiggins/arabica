<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
    <HTML>
      <BODY>
       
          <xsl:for-each select="bookstore/magazine">
		<xsl:sort select="@frequency" order="ascending"/>
		<xsl:sort select="title" order="ascending"/>
         <xsl:value-of  select="title"/> is a <xsl:value-of select="@style"/> magazine published <xsl:value-of select="@frequency"/> 


         </xsl:for-each> 
	      
      </BODY>
    </HTML>
  </xsl:template>
</xsl:stylesheet>
