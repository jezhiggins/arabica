<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:include href="MultipltKeysInclude.inc"/>

    <xsl:template match="prices">
	<out>
	<xsl:for-each select="key('prices', 'ddd')[@foo='1']">
		<xsl:value-of select="."/>
        </xsl:for-each>

	<xsl:call-template name="temp1"/> 
        </out>   
    </xsl:template>

    <xsl:key name="prices" match="price" use="@attr"/>

</xsl:stylesheet>
