<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
  <xsl:template match="/">
    <HTML>
      <BODY>
       
          
          <xsl:for-each select="sorttest/numbers[@dtype = 'text']">

		
	<xsl:for-each select="no">
		<xsl:sort select="." data-type="number"/>
		<xsl:value-of select="."/> is at position <xsl:value-of select="@pos"/><br/>
	</xsl:for-each>
            <br/>

          </xsl:for-each>

         
      </BODY>
    </HTML>
  </xsl:template>
</xsl:stylesheet>
