<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">  
 

<xsl:output method="html" omit-xml-declaration="yes" indent="no"/>
<xsl:output method="html" omit-xml-declaration="yes" indent="no"/>
<xsl:output method="xml" omit-xml-declaration="no" indent="no"/>
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

<xsl:template match="xslTutorial">  
<xsl:apply-templates/>   
</xsl:template>  

<xsl:template match="*">
<xsl:value-of select="name()"/><xsl:apply-templates/>  
</xsl:template>

</xsl:stylesheet>  
