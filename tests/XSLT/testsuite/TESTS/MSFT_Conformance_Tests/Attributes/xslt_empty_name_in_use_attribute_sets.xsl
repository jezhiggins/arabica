<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:variable name="var1">var1</xsl:variable>
    <xsl:output encoding="UTF-16" omit-xml-declaration="yes" indent="yes"/>

    <xsl:attribute-set name="empty"/>

    <xsl:attribute-set name="simple">
        <xsl:attribute name="attr">simple</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="foo">
        <xsl:attribute name="att-{$foo}">foo</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="bar">
        <xsl:attribute name="{$var1}{$param1}">bar</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="use-simple" use-attribute-sets="simple">
        <xsl:attribute name="us-attr">use-simple1</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/*">
	<Testing> 
		<xsl:apply-templates/>
		<l0 xsl:use-attribute-sets="bar"> 
		<l1 xsl:use-attribute-sets=""> 
		<l2 xsl:use-attribute-sets="foo"> 
		<l3> 
		<l4 xsl:use-attribute-sets="bar"> 
		<l5> 
		<l6> 
		<l7 xsl:use-attribute-sets="foo">
		</l7> </l6> </l5> </l4> </l3> </l2> </l1> </l0>
	</Testing>
    </xsl:template>

    <xsl:template match="node()"/>

    <xsl:param name="param1">param1</xsl:param>
    <xsl:variable name="foo">foo</xsl:variable>
</xsl:stylesheet>
