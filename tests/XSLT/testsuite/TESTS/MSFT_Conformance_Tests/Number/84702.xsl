<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting - empty attribute value -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/06/2000 -->


<xsl:template match="/">  
	<TABLE>  
		<xsl:for-each select="//n">  
			<TR><TD>  
				<TD>
					<xsl:number count = "" /> 
					<xsl:value-of select = "text()"/>										
				</TD>
			</TD></TR>  
		</xsl:for-each>  
	</TABLE>  
</xsl:template>  

</xsl:stylesheet>  
