<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 
 
<xsl:output method="xml" version="1.0" encoding="UTF-16"  omit-xml-declaration="yes"/>  

<xsl:template match="xslTutorial">  
<xsl:apply-templates/>  
</xsl:template>  

<xsl:template match="*">
<xsl:value-of select="name()"/><xsl:apply-templates/>  
</xsl:template>


</xsl:stylesheet>  
