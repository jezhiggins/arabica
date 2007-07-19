<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:test="http://localhost/test.xsd" version="1.0" >

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
     <xsl:apply-templates select="//element">
	<xsl:sort select="@test:foo" data-type="number"/>
     </xsl:apply-templates>
</xsl:template>

<xsl:template match="element">
     <xsl:value-of select="@name"/>,  
</xsl:template>

</xsl:stylesheet>