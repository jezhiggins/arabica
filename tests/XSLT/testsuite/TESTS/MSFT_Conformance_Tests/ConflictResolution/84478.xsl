<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


 <xsl:template match="/">
	
		<xsl:apply-templates/>
	
 </xsl:template>

<xsl:template match="*" priority="1.">
	<SPAN style="color=green"><xsl:value-of select="name()"/>
: 
	</SPAN>
  </xsl:template>

  <xsl:template match="*" priority="-1.">
	<SPAN style="color=red" > BUG
<xsl:value-of select="name()"/>: <xsl:value-of select="."/> </SPAN>
<br/><xsl:apply-templates/>
  </xsl:template>

<xsl:template match="text()" priority="-20"/>




</xsl:stylesheet>
