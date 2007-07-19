<!-- Error Case -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

	<xsl:template match="/">

        <x/>

        <!-- xsl:apply-imports must be empty, even in fwd-compat mode -->
        <xsl:apply-imports>
            <xsl:new>
                <xsl:fallback/>
            </xsl:new>
        </xsl:apply-imports>
    
    </xsl:template>

</xsl:stylesheet>
