<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:import href="91116d.xsl"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>


<xsl:template match="book[@style='aubiography']">
    <SPAN style="color=green">
    From B <xsl:value-of select="name()"/> : <xsl:value-of select="title"/> 
    </SPAN><br/>
    <xsl:apply-templates />
</xsl:template>

<xsl:template match="text()" >
</xsl:template>

</xsl:stylesheet>