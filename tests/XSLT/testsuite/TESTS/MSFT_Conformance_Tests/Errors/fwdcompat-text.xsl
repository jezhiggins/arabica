<!-- Error Case -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

	<xsl:template match="/">

        <x/>

        <!-- xsl:text must contain only text, even in fwd-compat mode -->
        <xsl:text>
            <xsl:new>
                <xsl:fallback/>
            </xsl:new>
        </xsl:text>
    
    </xsl:template>

</xsl:stylesheet>
