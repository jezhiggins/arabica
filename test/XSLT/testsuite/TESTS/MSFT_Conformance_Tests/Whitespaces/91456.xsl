<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:my="http://my.com">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" indent="no"/>

    <!-- This preserve should override all imported strip-space elements -->
    <xsl:strip-space elements="*"/>

    <!-- Include stylesheet that imports another stylesheet -->
    <xsl:include href="include-strip.inc"/>

    <!-- This strip should override the imported preserve element -->
    <xsl:strip-space elements="p"/>

	<xsl:template match="/">

        <xsl:copy-of select="//span"/>

        <xsl:copy-of select="//div/p"/>

	</xsl:template>

</xsl:stylesheet>
