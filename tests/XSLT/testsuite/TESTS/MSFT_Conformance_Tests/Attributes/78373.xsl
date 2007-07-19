<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
        <xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

      <xsl:template match="/">
        <root>
                <xsl:attribute name="xml:space" >default</xsl:attribute>
                <xsl:attribute name="xml:space" namespace="abc">preserve</xsl:attribute>
                <xsl:attribute name="xml:lang" >en</xsl:attribute>
                <xsl:attribute name="mode">b</xsl:attribute>
                <xsl:attribute name="xsl:version" >a</xsl:attribute>
                <xsl:attribute name="xmlns:xsl" namespace="abc">b</xsl:attribute>
		<xsl:element name="a">
			<xsl:attribute name="b" namespace="b"/>
		<xsl:element name="a">
			<xsl:attribute name="a:b" namespace="b"/>
		<xsl:element name="a">
			<xsl:attribute name="a:b" namespace="b"/>
		</xsl:element >
		</xsl:element >
		</xsl:element >
        </root>
      </xsl:template>

      <xsl:template match="text()" />
</xsl:stylesheet>
