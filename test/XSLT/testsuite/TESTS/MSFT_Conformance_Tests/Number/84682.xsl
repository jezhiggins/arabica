<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="yes" />

	<!-- Number Formatting - level = "multiple" -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/02/2000 -->

	<xsl:template match="/">  
		<TABLE BORDER="1">  
			<TR><TH>numbering output</TH><TH>text</TH></TR>  
			<xsl:for-each select="//chapter">  
			<TR><TD>  
			<xsl:number level="multiple"/>  
			</TD><TD>  
			<xsl:value-of select="./text()"/>  
			</TD></TR>  
			</xsl:for-each>  
		</TABLE>  
	</xsl:template>  

</xsl:stylesheet>

