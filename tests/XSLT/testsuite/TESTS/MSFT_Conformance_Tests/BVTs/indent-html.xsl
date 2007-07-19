<!-- UTF-8 -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:foo="http://my.com">

    <!-- Test combinations of <block> and <inline> next to each other -->
    <!-- Block elements are HTML block elements or elements with a namespace -->
    <div> <b> <x> </x> </b> </div> <div> <foo:x> </foo:x> </div> <b> <div/> </b>

    <!-- Text before and after <block> and <inline> elements -->
    <div> Text <b> Text <x> Text </x> Text </b> Text </div> Text <foo:x/>

    <!-- Comments & PI's -->
    <div> <xsl:comment/> <xsl:comment/> <b> <xsl:comment/> <xsl:comment/> </b> <xsl:comment/> <xsl:comment/> </div> <xsl:comment/> <xsl:comment/> <div/>
    <div> <xsl:processing-instruction name="my-pi"/> <b> <xsl:processing-instruction name="my-pi"/> </b> <xsl:processing-instruction name="my-pi"/> </div> <xsl:processing-instruction name="my-pi"/> <div/>

    <!-- Ignored nodes (DOCUMENT) -->
    <xsl:variable name="foo"><b>Hello</b></xsl:variable> <xsl:variable name="text">Hello</xsl:variable>
    <div> <xsl:copy-of select="$foo"/> </div> <xsl:copy-of select="$text"/> <div/>

    <!-- With empty elements -->
    <img> <img>Hello</img> </img> <link> <link/> </link> Hello <link/>

</html>
