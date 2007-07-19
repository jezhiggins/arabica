<!-- UTF-8 -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.http.com">
    <xsl:text>&#10;</xsl:text>

    <!-- Test various combinations of name and namespace AVT's -->
    <xsl:element name="xml" namespace="Hello World"><xsl:text>&#10;</xsl:text>
        <xsl:element name="{.//first-name}" namespace="Hello World2"/><xsl:text>&#10;</xsl:text>
        <xsl:element name="foo" namespace="{.//last-name}"/><xsl:text>&#10;</xsl:text>
        <xsl:element name="{.//first-name}" namespace="{.//last-name}"/><xsl:text>&#10;</xsl:text>
    </xsl:element><xsl:text>&#10;</xsl:text>

    <!-- Test namespace with attribute; make sure default ns not used by attribute; name parsing should use in-scope URN's -->
    <xsl:element name="xml" namespace="http://my.com" xmlns:real-ns="http://my.com">
        <xsl:attribute name="bar"/>
        <xsl:attribute name="foo" namespace="http://my.com2"/>
        <xsl:attribute name="xml:foo"/>
        <xsl:attribute name="xsl:foo"/>
        <xsl:attribute name="real-ns:foo"/>
    </xsl:element><xsl:text>&#10;</xsl:text>

</html>
