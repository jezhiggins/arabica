<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:template match="/">

        <x xsl:version="2.0">
            <!-- Enter forwards-compatibility mode -->
            <!-- Don't recognize xsl:version on instruction element -->
            <xsl:new xsl:version="1.0">
                <new-feature-content/>
                <xsl:fallback>
                    <feature-not-supported/>
                </xsl:fallback>
            </xsl:new>

            <xsl:if test="true()">
                <!-- Make sure 2.0 is still in effect -->
                <xsl:new>
                    <xsl:fallback>
                        <feature-not-supported/>
                    </xsl:fallback>
                </xsl:new>
            </xsl:if>
        </x>
    
    </xsl:template>

</xsl:stylesheet>
