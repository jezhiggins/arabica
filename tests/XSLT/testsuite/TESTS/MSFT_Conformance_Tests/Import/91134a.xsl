<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:include href="91134b.xsl"/>

<xsl:template match="book[@style='autobiography']" priority="1">
    <I>
    From A  <xsl:value-of select="name()"/> : <xsl:value-of select="title"/>        
    <xsl:apply-templates/> 
    </I>        
</xsl:template>



<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>