<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Test case for bug 71240, duplicate parameter in call template -->

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template name = "foo">
    	<xsl:call-template name="test">
         	<xsl:with-param name="foo"/>
         	<xsl:with-param name="foo"/>
    	</xsl:call-template>
    </xsl:template>

    <xsl:apply-templates>
    	<xsl:template name="test" match="/" />
    </xsl:apply-templates>

</xsl:stylesheet>