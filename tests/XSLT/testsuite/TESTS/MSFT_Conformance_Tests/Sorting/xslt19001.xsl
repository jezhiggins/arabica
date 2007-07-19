<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
<TABLE>  
<xsl:for-each select="//car">  
<xsl:sort data-type="number" select="@id" order="descending"/>  
<TR><TH><xsl:text> Car-</xsl:text> <xsl:value-of  
select="@id"/></TH></TR>  
</xsl:for-each>  
</TABLE>  
</xsl:template>  
</xsl:stylesheet>  


