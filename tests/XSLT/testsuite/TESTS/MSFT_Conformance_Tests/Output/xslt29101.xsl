<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">  
 
<xsl:output version="1.0" omit-xml-declaration="yes"/>  

<xsl:template match="xslTutorial">  
<xsl:apply-templates/>  
</xsl:template>  

<xsl:template match="*">
<xsl:value-of select="name()"/><xsl:apply-templates/>  
</xsl:template>


</xsl:stylesheet>  
