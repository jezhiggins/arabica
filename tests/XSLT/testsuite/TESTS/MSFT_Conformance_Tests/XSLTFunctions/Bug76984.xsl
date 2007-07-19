<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >

	<xsl:output method="xml" indent="yes" encoding="utf-8" omit-xml-declaration="yes"/>

	<xsl:variable name="var" select="document(root/foo/@doc)"/>

	<xsl:template match="/">
		
		<xsl:for-each select="$var">
			
			<row>
			
			<xsl:for-each select="$var">
				
				<col><xsl:value-of select="position()" /></col>

			</xsl:for-each>	
	
			</row>
		
		</xsl:for-each>		

        </xsl:template>

</xsl:stylesheet>
