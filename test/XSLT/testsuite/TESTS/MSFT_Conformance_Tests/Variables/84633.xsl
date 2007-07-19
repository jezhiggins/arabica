<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Self referencing of an xsl:variable is not allowed -->
<!-- Created : Khalil Jabrane -->
<!-- Date: 03/26/2000 -->
    
<xsl:variable name="myVariable"> 
	<xsl:value-of select="$myVariable"/>
</xsl:variable>

</xsl:stylesheet>