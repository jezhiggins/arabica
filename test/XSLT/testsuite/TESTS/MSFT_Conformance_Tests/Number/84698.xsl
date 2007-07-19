<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

<!-- XSLT: Number formatting - value attribute -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 04/05/2000 -->

<xsl:template match="/">  
	<TABLE>  
		<xsl:for-each select="//n">  
			<TR><TD>  
				<xsl:number value="position()"/>  
				<xsl:value-of select="."/>  
			</TD></TR>  
		</xsl:for-each>  
	</TABLE>  
</xsl:template>  

</xsl:stylesheet>  
