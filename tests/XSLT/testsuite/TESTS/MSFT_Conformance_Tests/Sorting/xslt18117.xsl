<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="/">
Sort by @d,@e,@c,@b, and then a3 
<xsl:for-each select="xslSort/Sort/a3">
  
	<xsl:sort select="a3[c]">a3</xsl:sort> 
	<xsl:sort select="a3[e]"/> 
	<xsl:sort select="a3[c]"/> 
	<xsl:sort select="a3[b]"/> 

	-name:<xsl:value-of select="name()"/>
	-d:<xsl:value-of select="@d"/>
	-e:<xsl:value-of select="@e"/>
	-c:<xsl:value-of select="@c"/>
	-b:<xsl:value-of select="@b"/>	
	=<xsl:value-of select="."/>
  </xsl:for-each>


  
  </xsl:template>
 </xsl:stylesheet>
