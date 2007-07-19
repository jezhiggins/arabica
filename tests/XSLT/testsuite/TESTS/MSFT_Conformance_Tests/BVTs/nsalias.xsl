<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:axsl="http://my.com" xmlns:default="http://default"
    exclude-result-prefixes="axsl default">

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" indent="yes"/>

    <!-- Default namespace-alias -->
    <xsl:namespace-alias stylesheet-prefix="#default" result-prefix="axsl"/>
    <xsl:namespace-alias stylesheet-prefix="default" result-prefix="#default"/>

    <!-- Alias namespace to itself -->
    <xsl:namespace-alias stylesheet-prefix="self" result-prefix="self" xmlns:self="http://self"/>

    <!-- Use aliases within a result-tree-fragment -->
    <xsl:variable name="rtf">
        <axsl:template match="/" axsl:version="2.0"/>
    </xsl:variable>

	<xsl:template match="/">
        <!-- Test aliased element, attribute, namespace node -->
        <axsl:stylesheet axsl:version="1.0" xmlns:axsl="http://my.com">
            <!-- Test aliases in an RTF -->
            <xsl:copy-of select="$rtf"/>
        </axsl:stylesheet>

        <!-- Test various node types -->
        <!-- Comment -->
        <?my-pi?>
        <x>PCData <![CDATA[CData]]></x>

        <!-- Default namespace, attributes with null namespace -->
        <x attr=""/>
        <self:x self:attr="" xmlns:self="http://self"/>
        <y xmlns="http://y" attr="">
            <default:x default:x="" xmlns:default="http://default"/>
        </y>

	</xsl:template>

    <!-- axsl is alias for multiple results, second should override -->
    <xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="self" xmlns:self="http://self"/>

    <!-- Forward namespace-alias declaration -->
    <xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>

</xsl:stylesheet>
