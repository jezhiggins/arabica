<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:template match="/">
        <override-slash2/>
	<xsl:apply-templates/>
    </xsl:template>

</xsl:stylesheet>
