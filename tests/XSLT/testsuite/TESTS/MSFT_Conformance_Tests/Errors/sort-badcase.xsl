<!-- Error Case -->
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>
		
	<xsl:template match="/">
        <xsl:for-each select="bookstore">
            <xsl:sort case-order="unknown"/>
        </xsl:for-each>
	</xsl:template>

</xsl:stylesheet>

