<?xml version="1.0"?> 
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="xslNumbering">
          <xsl:for-each select="n">
	  <xsl:number level = "single" value="position()" format="(01)" />
	  <xsl:value-of select="."/>
	  </xsl:for-each>
	</xsl:template>
        
</xsl:stylesheet>

