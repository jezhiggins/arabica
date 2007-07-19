<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:dt="urn:uuid:C2F41010-65B3-11d1-A29F-00AA00C14882/" xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


 


 <xsl:template match="/">
	<xsl:apply-templates select="//@dt:*"/>
 </xsl:template>

<xsl:template match="@dt:style">
	<SPAN style="color=green" >
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/>
  </xsl:template>

  <xsl:template match="@dt:style" priority="-0.001">
- <SPAN style="color=red"><xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
</xsl:template>

<xsl:template match="@dt:dt" priority="0.00001">
	<SPAN style="color=green" >
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/>
  </xsl:template>

  <xsl:template match="@dt:dt" >
- <SPAN style="color=red"><xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
  </xsl:template>





<xsl:template match="*" priority="-20">
<span style="color:blue"><xsl:apply-templates/></span>
</xsl:template>
<xsl:template match="text()" priority="-20">
<span style="color:blue"><xsl:apply-templates/></span>

</xsl:template>

</xsl:stylesheet>
