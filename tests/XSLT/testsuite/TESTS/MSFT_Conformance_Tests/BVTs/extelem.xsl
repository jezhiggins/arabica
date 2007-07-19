<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    extension-element-prefixes="  xsl   #default   xsl  #default    #default  xsl" xmlns="http://default" xmlns:foo="http://my.com">

    <!-- extension-element-prefixes defined on xsl:stylesheet element do not apply to xsl:include subtrees -->
    <xsl:import href="inc/extelem.inc"/>

    <xsl:output encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

    <!-- This should not be treated as an extension-element -->
    <x/>

	<xsl:template match="/">

        <!-- extension-element-prefixes should be visible on the element upon which it is defined -->
        <foo:test1>
		    <foo:x xsl:extension-element-prefixes="foo" attr="val">
                <xsl:fallback>foo:x fallback instantiated</xsl:fallback>
            </foo:x>
        </foo:test1>

        <!-- extension element with default namespace of null should be recognized -->
        <foo:test2>
            <x xsl:extension-element-prefixes="  #default #default  #default" xmlns="">
                <xsl:fallback>#default:x fallback instantiated, where #default is null</xsl:fallback>
            </x>
        </foo:test2>

        <!-- extension element with default namespace of non-null should be recognized -->
        <foo:test3>
            <x>
                <xsl:fallback>#default:x fallback instantiated, where #default is non-null</xsl:fallback>
            </x>
        </foo:test3>

        <!-- xmlns defining an extension element namespace should not be output -->
        <foo:test4 xsl:extension-element-prefixes="bar bar bar bar bar bar bar bar bar bar bar bar" xmlns:bar="http://extension2"/>

        <!-- invalid prefix with colon in name -->
        <foo:test5 xsl:extension-element-prefixes="#default prefix:gi-not-allowed" xmlns="" xsl:version="2.0">
            <!-- Since we're in fallback mode, the invalid extension-element-prefixes attribute should be ignored, and no error should occur -->
            <x/>
        </foo:test5>

        <!-- invalid #default1 prefix -->
        <foo:test6 xsl:extension-element-prefixes="#default #default1" xmlns="" xsl:version="2.0">
            <!-- Since we're in fallback mode, the invalid extension-element-prefixes attribute should be ignored, and no error should occur -->
            <x/>
        </foo:test6>

        <!-- undefined prefix -->
        <foo:test7 xsl:extension-element-prefixes="#default undefined" xmlns="" xsl:version="2.0">
            <!-- Since we're in fallback mode, the invalid extension-element-prefixes attribute should be ignored, and no error should occur -->
            <x/>
        </foo:test7>

        <!-- extension-element-prefixes should not be recognized on an xsl instruction element -->
        <xsl:for-each select="bookstore" xsl:extension-element-prefixes="foo">
            <foo:test8/>
        </xsl:for-each>

        <!-- Allow imported stylesheet to execute -->
        <xsl:apply-imports/>

	</xsl:template>

</xsl:stylesheet>
