<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

  <xsl:template match="/">
    <span style="color=green">
 
          <p/>  <xsl:for-each select="bookstore/magazine/title">
				Title of Current Magazine: <xsl:value-of select="current()"/>
          	</xsl:for-each>
</span>

  
  </xsl:template>


</xsl:stylesheet>
