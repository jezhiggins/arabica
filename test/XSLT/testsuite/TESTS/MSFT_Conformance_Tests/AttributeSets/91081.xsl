<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="att"></xsl:attribute>
        <xsl:attribute name="att1">1</xsl:attribute>
        <xsl:attribute name="att2">2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
	<!-- attribute specified in the literal element will override what is in the attribute set -->
    	<foo xsl:use-attribute-set="foo" name="foo" att="abc" elem1="value1" elem2="value2" att1="def">
		<xsl:attribute name="name">blar</xsl:attribute>
		<xsl:attribute name="att1">	</xsl:attribute>
		<xsl:attribute name="att2">testing</xsl:attribute>
	</foo>
	
    	<xsl:element name="foo" xsl:use-attribute-sets="foo" >
		<xsl:attribute name="bar">bar</xsl:attribute>
	</xsl:element>

	<!-- xsl:copy-of should not allow use-attribute-sets according to spec -->
	<xsl:copy-of select="//price[text()='08']">
	</xsl:copy-of>

	<!-- this a-tp call the xsl:template below to process copy -->
	<xsl:apply-templates/>
    </xsl:template>

    
    <!-- only copy node and attibute (shallow clone) both book and title should have the foo attriburte sets -->
    <xsl:template match="//book | title | @*">
		<!-- xsl:copy don't take any specified attribute, thus att='asdf' is ignored -->
		<xsl:copy use-attribute-sets="foo" >
			<xsl:attribute name="att">value of att</xsl:attribute>
			<xsl:apply-templates select="node() | @* "/>
		</xsl:copy>
    </xsl:template>

    <!-- author should not have any attribute on it -->
    <xsl:template match="author">
	<xsl:copy>
		<xsl:apply-templates/>
	</xsl:copy>
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
