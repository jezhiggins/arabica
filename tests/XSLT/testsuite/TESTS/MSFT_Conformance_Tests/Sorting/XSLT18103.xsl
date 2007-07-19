<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    <HTML>
      <BODY>
       
          <xsl:for-each select="//elem">
		<xsl:sort select="ancestor::fruit/@name"/>
		
       
	fruit name: <xsl:value-of select="ancestor::fruit/@name"/>
  			<xsl:value-of  select="@a"/>

         </xsl:for-each> 
	      
      </BODY>
    </HTML>
  </xsl:template>
</xsl:stylesheet>
