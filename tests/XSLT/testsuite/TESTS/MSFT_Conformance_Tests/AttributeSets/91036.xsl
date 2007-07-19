<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="simple">
        <xsl:attribute name="attr">simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/" priority="1" >
	<xsl:for-each select="//magazine">
		<xsl:copy xsl:use-attribute-sets="should be ignored" foo="ignored" use-attribute-sets="simple"/>
		<xsl:copy use-attribute-sets="complex">
			<xsl:copy use-attribute-sets="complex simple"/>
		</xsl:copy>
		<xsl:copy use-attribute-sets="simple complex"/>
	</xsl:for-each>
    </xsl:template>

    <xsl:attribute-set name="complex">
        <xsl:attribute name="att1">complex1</xsl:attribute>
        <xsl:attribute name="{$x}">complex2</xsl:attribute>
    </xsl:attribute-set>

    <xsl:param name="x">param-att</xsl:param>
</xsl:stylesheet>
