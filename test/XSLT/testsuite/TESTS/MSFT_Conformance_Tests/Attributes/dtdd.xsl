<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
		<xsl:for-each select="DL/*" >
			<xsl:value-of select="name()"/>^
			<xsl:for-each select="..">
				<xsl:value-of select="name()"/>^
			</xsl:for-each>	
			<xsl:for-each select="ancestor::*">
				<xsl:value-of select="name()"/>^
			</xsl:for-each>
			-	
		</xsl:for-each> 
</xsl:template>
</xsl:stylesheet>