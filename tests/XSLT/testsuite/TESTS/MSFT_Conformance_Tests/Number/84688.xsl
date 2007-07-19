<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- Number Formatting - invalid level - null string -->
	<!-- Created : Khalil Jabrane -->
	<!-- Date: 04/03/2000 -->

	<xsl:template match="PERIODIC_TABLE">
	  <html>
	    <head><title>The Elements</title></head>
		  <body>
		    <table>
			  <tr><xsl:apply-templates select="ATOM"/></tr>
			</table>
		  </body>
	    </html>
	</xsl:template>

	<xsl:template match="ATOM">
	  <tr><xsl:apply-templates select="NAME"/></tr>
	</xsl:template>

	<xsl:template match="NAME">
	  <td><xsl:number level="singlegroupe"/></td>
	  <td><xsl:value-of select="."/></td>
	</xsl:template>


        
</xsl:stylesheet>

