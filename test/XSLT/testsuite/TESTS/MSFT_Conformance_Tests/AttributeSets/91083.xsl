<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="att"></xsl:attribute>
        <xsl:attribute name="att1">1</xsl:attribute>
        <xsl:attribute name="att2">2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
	<!-- test that specified att override attset -->
    	<foo xsl:use-attribute-set="foo" att="literal">
	</foo>

	<!-- test that xslatt override specified att -->
    	<foo xsl:use-attribute-set="foo" att="literal">
		<xsl:attribute name="att">xslattribute</xsl:attribute>
	</foo>
	
	<!-- test that xslatt override specified att -->
    	<foo xsl:use-attribute-set="foo" att="literal">
		<xsl:attribute name="att">xslattribute</xsl:attribute>
	</foo>

	<!-- test that xslatt override specified att -->
    	<xsl:element name="foo" xsl:use-attribute-sets="foo" >
		<xsl:attribute name="bar">bar</xsl:attribute>
	</xsl:element>

	<xsl:copy-of select="//price[text()='08']" >
	</xsl:copy-of>

	<xsl:apply-templates/>
    </xsl:template>

    
    <!-- only copy node and attibute (shallow clone) both book and title should have the foo attriburte sets -->
    <xsl:template match="//book | title | @*">
		<xsl:apply-templates select="node() | @* "/>
    </xsl:template>

    <!-- first-name should have koko attribute set on it -->
    <xsl:template match="first-name">
	<xsl:copy use-attribute-sets="foo">
		<xsl:attribute name="koko">koko</xsl:attribute>
		<xsl:attribute name="att">koko</xsl:attribute>
	</xsl:copy>
    </xsl:template>

    <!-- need this to write off text -->
    <xsl:template match="text()">
    </xsl:template>



</xsl:stylesheet>
