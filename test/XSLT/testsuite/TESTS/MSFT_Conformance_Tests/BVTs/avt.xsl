<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

        <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="bookstore">
		<!-- Test sort modifiers as AVT's -->
		<xsl:for-each select="book">
			<xsl:sort select=".//last-name" data-type="{'text'}" order="{'descending'}"/>
			<xsl:sort select=".//price" data-type="{'number'}"/>
			<xsl:sort select="title" order="{'ascending'}"/>
			<xsl:value-of select=".//last-name"/><xsl:text xml:space="preserve">    </xsl:text><xsl:value-of select="price"/>
		</xsl:for-each>

		<!-- Test various AVT's -->
		<test1 attr="{//last-name}" attr2="{//first-name}" attr3="//first-name" attr4="" attr5="{no-exist}"/>
		<test2 xmlns:my-ns="{'hello'}" xmlns="{'goodbye'}"/>
		<test3 attr="{//last-name}{//first-name}" attr2="{//last-name}" />
		<test4 attr="start{//last-name}" attr2="{//last-name}end" attr3="{//last-name}middle{//first-name}"/>
		<test5 attr="{{" attr2="}}" attr4="{{{//last-name}}}"/>
		<test6 attr="{//not-there}Hello{//not-there}"/>

		<!-- Test name as AVT -->
		<xsl:element name="{//last-name}">
			<xsl:attribute name="{//last-name}"/>
		</xsl:element>
		<xsl:processing-instruction name="{//last-name}"/>
		<xsl:comment>Hello</xsl:comment>

        <!-- Make sure global attributes with XSL namespace are stripped from literal result elements -->
        <elem xsl:version="1.0" xsl:humbug="value"/>

        <xsl:apply-templates select="book[1]"/>
	</xsl:template>

    <xsl:template match="book">

        <!-- Regression case for bug 57072 (use current() and document() within an AVT just after an xsl:template) -->
        <test7 attr="current: {current()/title}, document: {document('')/xsl:stylesheet/@version}"/>

    </xsl:template>

</xsl:stylesheet>
