<!-- Test case for bug # 70883 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:attribute-set name="simple">
        <xsl:attribute name="attr"/>
    </xsl:attribute-set>

    <xsl:template match="/">
	<e xsl:use-attribute-sets=" simple "/>
    </xsl:template>

</xsl:stylesheet>