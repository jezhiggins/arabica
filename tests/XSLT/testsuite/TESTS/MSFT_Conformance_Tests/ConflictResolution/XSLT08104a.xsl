<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >


 


 <xsl:template match="/">
	<xsl:apply-templates select="//my:*"/>
 </xsl:template>

<xsl:template match="my:*" priority="-.24999">
	<SPAN style="color=green">
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/>
  </xsl:template>

  <xsl:template match="my:*">
- <SPAN style="color=red"><xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>

  </xsl:template>


<xsl:template match="*" priority="-20">
<span style="color:blue"><xsl:apply-templates/></span>
</xsl:template>
<xsl:template match="text()" priority="-20">
<span style="color:blue"><xsl:apply-templates/></span>

</xsl:template>

</xsl:stylesheet>
