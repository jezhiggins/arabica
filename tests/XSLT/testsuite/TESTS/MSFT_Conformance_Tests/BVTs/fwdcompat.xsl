<xsl:stylesheet unknown="" extension-element-prefixes="#default #defaultBad" exclude-result-prefixes="#default #defaultBad" version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:import unknown="" href="inc/fwdcompat.inc"/>

    <xsl:output method="xml" encoding="UTF-8" omit-xml-declaration="yes" standalone="no" cdata-section-elements="cdata" indent="yes"/>

    <xsl:output method="raw" bom="yes" omit-xml-declaration="maybe" standalone="maybe" cdata-section-elements="cdata2 {$var}" indent="maybe"/>

    <xsl:top-level-2.0><content/></xsl:top-level-2.0>

    <xsl:attribute-set name="foo"><xsl:attribute name="foo"/></xsl:attribute-set>

    <xsl:attribute-set name="attr-set" use-attribute-sets="foo {" unknown="">
        <xsl:attribute name="attr"/>
    </xsl:attribute-set>

    <xsl:decimal-format unknown="" name="{" decimal-separator="xx" grouping-separator="xx" percent="xx"
                        per-mille="xx" zero-digit="xx" digit="xx" pattern-separator="xx" minus-sign="xx"/>

    <xsl:import/>

    <xsl:include href="inc/fwdcompat.inc" unknown=""/>

    <xsl:key name="foo" match="book" use="title"/>

    <xsl:namespace-alias unknown="" stylesheet-prefix="foo" result-prefix="foo" xmlns:foo="http://foo"/>

    <xsl:strip-space elements="*" unknown=""/>

    <xsl:preserve-space elements="*" unknown=""/>

    <xsl:template match="/" unknown="" priority="hello" name="{" mode="{">

        <test1><xsl:apply-imports unknown=""/></test1>

        <test2><xsl:apply-templates unknown="" mode="{" select="bookstore"/></test2>

        <test3><xsl:attribute name="x" unknown=""/></test3>

        <test4><xsl:call-template name="call-tmpl" unknown=""/></test4>

        <test5><xsl:choose unknown=""><xsl:when test="true()" unknown=""><x/></xsl:when><xsl:otherwise unknown=""/></xsl:choose></test5>

        <test6><xsl:comment name="{" namespace="{"/></test6>

        <test7><xsl:for-each select="bookstore"><xsl:copy name="{" use-attribute-sets="{"/></xsl:for-each></test7>

        <test8><xsl:copy-of select="bookstore/book[1]/author[1]/last-name"/></test8>

        <test9><xsl:element name="x" unknown="" use-attribute-sets="attr-set"/></test9>

        <test10><xsl:fallback unknown=""><xsl:new/></xsl:fallback></test10>

        <test11><xsl:for-each select="bookstore" unknown=""><x/></xsl:for-each></test11>

        <test12><xsl:if unknown="" test="true()"><x/></xsl:if></test12>

        <test13><xsl:number value="1" level="unknown" letter-value="unknown" lang="unknown" unknown=""/></test13>

        <test14><xsl:processing-instruction name="pi" namespace="unknown"/></test14>

        <test15><xsl:for-each select="//book/title/text()"><xsl:sort select="." lang="unknown" data-type="unknown" order="unknown" case-order="unknown" unknown=""/><xsl:copy/></xsl:for-each></test15>

        <test16><xsl:text unknown="" disable-output-escaping="maybe">text</xsl:text></test16>

        <test17><xsl:value-of unknown="" disable-output-escaping="maybe" select="'value'"/></test17>

        <!-- Make sure that cdata-sections-elements was set correctly (cdata2 should not be made into a CDATA node) -->
        <test18><cdata>Some text</cdata><cdata2>More text</cdata2></test18>

    </xsl:template>

    <xsl:template priority="-10" match="{$var}">

        <xsl:param name="foo" unknown=""><xsl:new/></xsl:param>

        <x avt="{"><xsl:new/></x>

        <xsl:template-elem-2.0><content/></xsl:template-elem-2.0>

        <xsl:apply-imports/>

        <xsl:apply-templates select="{"><xsl:with-param name="foo" select="{" unknown=""/></xsl:apply-templates>

        <xsl:attribute name="{" namespace="{"><xsl:new/></xsl:attribute>

        <xsl:call-template name="call-tmpl"/>

        <xsl:choose><xsl:when test="true"/></xsl:choose>

        <xsl:copy-of select="{"/>

        <xsl:message terminate="maybe"><xsl:new/></xsl:message>

        <xsl:number count="{" from="{" value="{"/>

        <xsl:for-each select="//book"><xsl:sort select="{"/><xsl:new/></xsl:for-each>

        <xsl:value-of select="{"/>

        <xsl:variable name="foo2" unknown=""><xsl:new/></xsl:variable>

    </xsl:template>

    <xsl:template match="bookstore" name="call-tmpl"><template-invoked/></xsl:template>

</xsl:stylesheet>
