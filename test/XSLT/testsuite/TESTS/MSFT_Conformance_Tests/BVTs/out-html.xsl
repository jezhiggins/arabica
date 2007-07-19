<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="http://my.com" exclude-result-prefixes="foo">

    <xsl:output method="html" version="4.0" encoding="iso-8859-1" media-type="text and html" doctype-public="public" doctype-system="system"/>

    <xsl:template match="/">

    <!-- Empty HTML Elements -->

        <!-- Simple -->
        <area/><base/><basefont/><br/><col/><frame/><hr/><img/><input/><isindex/><link/><meta/><param/>

        <!-- Ensure case insensitivity -->
        <AREA/><bAsE/><BaseFont/><bR/><Col/><FramE/><HR/><iMg/><InPut/><isIndex/><lInk/><MEta/><paRAM/><xsl:text>&#xA;</xsl:text>

        <!-- International characters & misspellings -->
        <Årëæ/><ßãçé/><basefont-/><b/><col1/><iframe/><h-r/><ìñþûï/><xsl:text>&#xA;</xsl:text>

        <!-- Not quite empty & content -->
        <hr></hr><area>Hello</area><xsl:text>&#xA;</xsl:text>

        <!-- Other HTML elements -->
        <html><title/><body><h1><br/><b>hello</b></h1></body></html>

        <!-- With namespaces -->
        <foo:area/><area xmlns="http://my.com"/><xsl:text>&#xA;</xsl:text>

    <!-- HTML elements with boolean attributes -->

        <!-- Simple -->
        <input checked="checked"/><xsl:text>&#xA;</xsl:text>
        <dir compact="compact"/><dl compact="compact"/><menu compact="compact"/><ol compact="compact"/><ul compact="compact"/><xsl:text>&#xA;</xsl:text>
        <object declare="declare"/><xsl:text>&#xA;</xsl:text>
        <script defer="defer"/><xsl:text>&#xA;</xsl:text>
        <button disabled="disabled"/><input disabled="disabled"/><optgroup disabled="disabled"/><option disabled="disabled"/><select disabled="disabled"/><textarea disabled="disabled"/><xsl:text>&#xA;</xsl:text>
        <img ismap="ismap"/><input ismap="ismap"/><xsl:text>&#xA;</xsl:text>
        <select multiple="multiple"/><xsl:text>&#xA;</xsl:text>
        <area nohref="nohref"/>
        <frame noresize="noresize"/>
        <hr noshade="noshade"/><xsl:text>&#xA;</xsl:text>
        <td nowrap="nowrap"/><th nowrap="nowrap"/><xsl:text>&#xA;</xsl:text>
        <textarea readonly="readonly"/><input readonly="readonly"/><xsl:text>&#xA;</xsl:text>
        <option selected="selected"/><xsl:text>&#xA;</xsl:text>

        <!-- Ensure case insensitivity -->
        <input Checked="cHeckEd" CHECKED="checked" checkED="CHecked"/><xsl:text>&#xA;</xsl:text>

        <!-- Boolean attributes only recognized on HTML elements which can have them -->
        <foo:input checked="checked"/><input checked="checked" xmlns="http://my.com"/><link checked="checked"/><not-html checked="checked"/><input foo:checked="checked"/><xsl:text>&#xA;</xsl:text>

        <!-- Attribute with empty value -->
        <input checked=""/><non-html checked=""/><xsl:text>&#xA;</xsl:text>

    <!-- HTML elements with URI attributes -->

        <!-- Simple -->
        <area href="&lt;&amp;{{Årëæ"/><link href="&lt;&amp;{{Årëæ"/><a href="&lt;&amp;{{Årëæ"/><base href="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <script src="&lt;&amp;{{Årëæ"/><input src="&lt;&amp;{{Årëæ"/><img src="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <img longdesc="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <input usemap="&lt;&amp;{{Årëæ"/><img usemap="&lt;&amp;{{Årëæ"/><object usemap="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <object classid="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <object codebase="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <object data="&lt;&amp;{{Årëæ"/><xsl:text>&#xA;</xsl:text>
        <q cite="&lt;&amp;{{Årëæ"/><blockquote cite="&lt;&amp;{{Årëæ"/><ins cite="&lt;&amp;{{Årëæ"/><del cite="&lt;&amp;{{Årëæ"/>
        <form action="&lt;&amp;{{Årëæ"/>
        <head profile="&lt;&amp;{{Årëæ"/>
        <script for="&lt;&amp;{{Årëæ"/>
        <table datasrc="&lt;&amp;{{Årëæ"/>

    <!-- Don't escape < in attribute values (if element namespace is null) -->

        <html name="&lt;hello&gt;"/>
        <foo:html name="&lt;hello&gt;"/><xsl:text>&#xA;</xsl:text>

    <!-- HTML script and style elements -->

        <!-- Simple -->
        <script>if (a &lt; b) foo()</script><xsl:text>&#xA;</xsl:text>
        <script><![CDATA[if (a < b) foo()]]></script><xsl:text>&#xA;</xsl:text>

        <style>&amp;&lt;&gt;</style><xsl:text>&#xA;</xsl:text>
        <style><![CDATA[&<>]]></style><xsl:text>&#xA;</xsl:text>

        <!-- Embedded elements -->
        <script>a &lt; b <embedded> a &lt; b </embedded> a &lt; b </script><xsl:text>&#xA;</xsl:text>

        <!-- Attribute text -->
        <script attr="a &amp; b"/><xsl:text>&#xA;</xsl:text>

    <!-- Ampersands in attribute values (if element namespace is null) -->

        <BODY bgcolor="&amp;{{randomrbg}}"/>
        <BODY><xsl:attribute name="bgcolor">&amp;<xsl:value-of select="'{randomrbg}'"/></xsl:attribute></BODY>
        <BODY bgcolor="begin&amp;{{&amp;end&amp;}}"/>
        <AREA href="&amp;{{randomrbg}}"/>

        <foo:AREA href="&amp;{{randomrbg}}"/>

    <!-- Insert META element after HEAD -->

        <HEAD/>
        <HEAD>
            <H1>Hello</H1>
        </HEAD>

    <!-- Non-empty HTML elements should always have an end-tag -->
        <BODY/> <BODY></BODY> <BODY> </BODY>
        <DIV> <SPAN/> <SPAN></SPAN> <SPAN> </SPAN> </DIV>

    </xsl:template>

</xsl:stylesheet>
