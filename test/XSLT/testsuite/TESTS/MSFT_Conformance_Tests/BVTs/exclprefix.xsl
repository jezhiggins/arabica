<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:ext="http://ext" xmlns:ns1="http://ns1"
    exclude-result-prefixes="   ns1   ext   ">

    <!-- exclude-result-prefixes defined on xsl:stylesheet element do not apply to xsl:include subtrees -->
    <xsl:import href="inc/exclprefix.inc"/>

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <xsl:template match="/">

        <x xmlns:ns2="http://ns2" xsl:exclude-result-prefixes="ns2">
            <xsl:if test="true()" xmlns:ns2="http://ns2">
                <y xmlns:ns2="http://ns2"/>
            </xsl:if>
        </x>

        <!-- Previous exclude-result-prefixes should not apply here -->
        <x xmlns:ns2="http://ns2"/>

        <!-- Exclude default ns -->
        <ns1:x xmlns="http://default" xsl:exclude-result-prefixes="#default"/>

        <!-- Ignore xsl:exclude-result-prefixes on instructions and extension elements -->
        <ext:x xsl:extension-element-prefixes="ext" xmlns:ns3="http://ns3" xsl:exclude-result-prefixes="ns3">
            <xsl:fallback xsl:exclude-result-prefixes="ns3">
                <x/>
            </xsl:fallback>
        </ext:x>

        <!-- Even if excluded, namespaces still may need to be output -->
        <ns1:x/>

        <!-- Allow imported template to execute -->
        <xsl:apply-imports/>

    </xsl:template>

</xsl:stylesheet>
