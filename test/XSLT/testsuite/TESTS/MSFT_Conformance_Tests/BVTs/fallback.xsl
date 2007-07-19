<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <!-- Arbitrary template content allowed -->
        <test1>
            <xsl:element name="x">
                <xsl:new attr="val" attr2="val2">
                    <xsl:fallback>
                        <!-- Try different types of content -->
                        <?my-pi?>
                        <y>
                            <xsl:text>last-name: </xsl:text>
                            <xsl:value-of select="(//author)[1]/last-name"/>
                        </y>
                    </xsl:fallback>
                </xsl:new>
            </xsl:element>
        </test1>

        <!-- Recursive fallbacks (make certain that xml:space is consulted) -->
        <test2> <xsl:new xml:space="preserve"> <xsl:fallback xml:space="default"> <xsl:new> <xsl:fallback xml:space="preserve"> </xsl:fallback> </xsl:new> </xsl:fallback> </xsl:new> </test2>

        <!-- Ignore the xsl:fallback element -->
        <test3><xsl:fallback><content/></xsl:fallback></test3>

        <!-- Reference template variable from within fallback -->
        <xsl:variable name="foo" select="'foo-value'"/>

        <xsl:new attr="val">
            <new-feature-content attr="val"/>
            <xsl:fallback>
                <test4>
                    <xsl:value-of select="$foo"/>
                </test4>
            </xsl:fallback>

            Some text

            <!-- Multiple fallback children -->
            <xsl:fallback>
                <test5>
                    <xsl:value-of select="$foo"/>
                </test5>
            </xsl:fallback>
        </xsl:new>

    </xsl:template>

</xsl:stylesheet>
