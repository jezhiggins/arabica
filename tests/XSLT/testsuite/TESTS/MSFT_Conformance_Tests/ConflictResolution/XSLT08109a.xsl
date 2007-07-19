<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >
<xsl:include href="lowpribooks17.xsl"/>
<xsl:template match="/">
<xsl:apply-templates/>
</xsl:template>
 


 <xsl:template match="book">
- <SPAN style="color=yellow">
<xsl:value-of select="name()"/> :<xsl:value-of select="title"/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>

 <xsl:template match="book|book/title" priority="0.25">
- <SPAN style="color=brown">
<xsl:value-of select="name()"/> :</SPAN>
<SPAN style="color:blue">
<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>


 <xsl:template match="book">
- <SPAN style="color=red">
<xsl:value-of select="name()"/> :<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>

 <xsl:template match="book/title">
- <SPAN style="color=green">
book <xsl:value-of select="name()"/> :<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>
 <xsl:template match="magazine|magazine/title" priority="0.6">
- <SPAN style="color=brown">
<xsl:value-of select="name()"/> :</SPAN>
<SPAN style="color:blue">
<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>


 <xsl:template match="magazine">
- <SPAN style="color=red">
<xsl:value-of select="name()"/> :<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>

 <xsl:template match="magazine/title">
- <SPAN style="color=green">magazine <xsl:value-of select="name()"/> :<xsl:value-of select="."/> </SPAN><br/><xsl:apply-templates/>
  </xsl:template>

<xsl:template match="*">
<xsl:apply-templates/>
</xsl:template>


<xsl:template match="text()">
	
</xsl:template>

</xsl:stylesheet>
