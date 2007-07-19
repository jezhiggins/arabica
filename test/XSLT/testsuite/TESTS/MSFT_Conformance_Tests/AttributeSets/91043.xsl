<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:variable name="var1">var1</xsl:variable>
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="foobar">
        <xsl:attribute name="foobar">simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="trick">
        <xsl:attribute name="foobar"> ERROR </xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="use-foobar" use-attribute-sets="foobar">
        <xsl:attribute name="us-attr">use-foobar</xsl:attribute>
        <!-- <xsl:attribute name="xmlns:my">xmlns:my</xsl:attribute> -->
    </xsl:attribute-set>

    <xsl:template match="/*">
	<Testing> 
		<xsl:apply-templates/>
		<l1 xsl:use-attribute-sets="foobar"/> 
	</Testing>
    </xsl:template>

    <xsl:template match="node()"/>

</xsl:stylesheet>
