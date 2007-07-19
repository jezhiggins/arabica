<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:include href="91135c.xsl"/>

<xsl:template match="book[@style='autobiography']" priority="2">
	<SPAN style="color=red">
	From B  <xsl:value-of select="name()"/> : <xsl:value-of select="title"/>   
    <xsl:apply-templates/>  
    </SPAN><br/>
</xsl:template>

<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>