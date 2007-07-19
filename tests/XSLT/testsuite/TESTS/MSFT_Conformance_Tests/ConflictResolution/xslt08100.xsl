<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 

xmlns="urn:http//www.placeholder-name-here.com/schema/">
 


 <xsl:template match="/">
	<root>
		<xsl:apply-templates select="//book | //@*" />
	</root>
 </xsl:template>

<xsl:template match="*" priority="-.49">
	<SPAN style="color=green" >
<xsl:value-of select="name()"/>
	: <xsl:value-of select="*"/> </SPAN>
  </xsl:template>

  <xsl:template match="*">
	<SPAN style="color=red" >
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/><xsl:apply-templates/>
  </xsl:template>

<xsl:template match="@*">
	<SPAN style="color=black" > 
<xsl:value-of select="name()"/>
		: <xsl:value-of select="."/> </SPAN>
<br/><xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="@*" priority="-.51">
	<SPAN style="color=yellow" >
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/><xsl:apply-templates/>
  </xsl:template>

<xsl:template match="text()" priority="-20"/>




</xsl:stylesheet>
