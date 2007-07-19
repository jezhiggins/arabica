<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">    

       
          <xsl:for-each select="sorttest/key">
		<xsl:sort select="@lang"/>
		<xsl:sort select="."/>
		<xsl:value-of select="@lang"/>:  <xsl:value-of 		select="."/><br/>
         </xsl:for-each> 
<hr/>	 
<xsl:for-each select="sorttest/key">
		
		<xsl:sort select="."/>
		<xsl:value-of select="@lang"/>:  <xsl:value-of 		select="."/><br/>
         </xsl:for-each>     

  </xsl:template>

</xsl:stylesheet>
