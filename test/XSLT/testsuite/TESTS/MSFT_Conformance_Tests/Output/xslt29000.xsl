<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
xmlns:user="http://mycompany.com/mynamespace"	>  
 
<user:output method="html"  indent="no"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
<xsl:template match="xslTutorial">  
<xsl:apply-templates/>   
</xsl:template>  

<xsl:template match="*">
<xsl:value-of select="name()"/><xsl:apply-templates/>  
</xsl:template>


</xsl:stylesheet>  
