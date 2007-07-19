<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="bookstore">
<B><xsl:apply-templates select="magazine">
		<xsl:sort select="@frequency"/>
		<xsl:sort select="title"/>
</xsl:apply-templates></B>   
</xsl:template>

<xsl:template match="magazine">  <SPAN>  
         	<xsl:value-of  select="title"/> is a <xsl:value-of select="@style"/> magazine published <xsl:value-of select="@frequency"/> 
         	</SPAN>
</xsl:template>
</xsl:stylesheet>

