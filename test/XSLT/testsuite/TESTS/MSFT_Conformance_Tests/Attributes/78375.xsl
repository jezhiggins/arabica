<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="xml" omit-xml-declaration="yes"/>
<xsl:template match="/">
        <root xmlns:a="a">
	   <xsl:element name="a:a" >
                <xsl:attribute name="foo" namespace="bar">abc</xsl:attribute>
	   </xsl:element>
        </root>
</xsl:template>
</xsl:stylesheet>
