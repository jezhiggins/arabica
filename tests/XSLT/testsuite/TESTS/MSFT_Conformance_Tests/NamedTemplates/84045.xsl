
<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>  
 
<xsl:template match="/">  
	
	<xsl:call-template name="foobar" mode="m"/>
	
	
</xsl:template>  
 


<xsl:template  match="magazine" mode="m" priority="2">  
MODE M PRI 2 
</xsl:template>

<xsl:template name="bar" match="magazine" mode="m" priority="1">  
MODE M PRI 1
</xsl:template>

<xsl:template name="foobar" match="magazine" mode="x" priority="1">  
MODE X PRI 1
</xsl:template>

<xsl:template match="*|text()">
<xsl:apply-templates />
</xsl:template>
<xsl:template match="*|text()" mode="m">
<xsl:apply-templates mode="m"/>
</xsl:template>

<xsl:template match="*|text()" mode="x">
<xsl:apply-templates mode="x"/>
</xsl:template>
</xsl:stylesheet>  