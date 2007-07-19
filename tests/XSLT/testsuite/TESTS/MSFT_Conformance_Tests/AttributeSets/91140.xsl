<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:import href="http://webxtest/testcases/91140a.xsl"/>
    <xsl:output encoding="UTF-16" omit-xml-declaration="no" indent="yes"/>

    <xsl:attribute-set name="foo" use-attribute-sets="bar">
        <xsl:attribute name="attr">123</xsl:attribute>
    </xsl:attribute-set>

    <xsl:template match="/">
    	<foo xsl:use-attribute-sets="foo"/>
    </xsl:template>

    <xsl:attribute-set name="foo" >
        <xsl:attribute name="attr">abc</xsl:attribute>
    </xsl:attribute-set>

    <xsl:attribute-set name="foo" >
        <xsl:attribute name="attr">XYZ</xsl:attribute>
    </xsl:attribute-set>

</xsl:stylesheet>
