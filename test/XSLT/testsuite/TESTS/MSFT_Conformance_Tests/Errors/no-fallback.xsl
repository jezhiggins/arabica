<!-- Error Case -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

	<xsl:template match="/">

        <x/>

        <!-- No fallback exists, error should be thrown at run-time -->
        <xsl:new/>
    
    </xsl:template>

</xsl:stylesheet>
