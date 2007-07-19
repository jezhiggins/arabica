<!-- UTF-8 -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Name of element is 'xml' -->
    <xsl:element name="xml">

        <!-- Don't output namespace declaration for xml prefix -->
        <xsl:attribute name="xml:space"/>

        <!-- Shouldn't output xmlns:bar="" -->
        <xsl:attribute name="xmlns:bar" namespace=""></xsl:attribute>

        <!-- Attempt to output namespace node using xsl:attribute. -->
        <xsl:attribute name="xmlns:foo" namespace="http://my.com2">http://my.com</xsl:attribute>

        <!-- Name begins with characters 'xml' -->
        <xsl:processing-instruction name="xml-stylesheet"/>

        <!-- Output element with name in XSL namespace -->
        <xsl:element name="xsl:foo">

            <!-- Output attribute with name in XSL namespace -->
            <xsl:attribute name="xsl:foo"/>

        </xsl:element>

        <!-- Output default namespace declaration "xmlns", attributes using default namespace declaration -->
        <xsl:element name="foo" xmlns="http://my.com">
            <xsl:attribute name="attr"/>
            <xsl:attribute name="attr" namespace="http://my.com.2"/>
            <xsl:attribute name="attr2" xmlns=""/>
        </xsl:element>

        <!-- Output element & attribute with non-empty prefix and null namespace (prefix should be truncated) -->
        <xsl:element name="foo" xmlns="http://my.com">
            <xsl:attribute name="foo:bar" namespace=""/>
            <xsl:element name="foo:bar" namespace=""/>
        </xsl:element>

        <!-- Bug 47284: Output element with empty prefix and empty namespace (extra xmlns="" attributes shouldn't be output) -->
        <xsl:element name="foo" namespace="">
            <xsl:element name="foo:bar" namespace=""/>
        </xsl:element>

        <!-- Bug 56986: Output element/attribute with reserved prefix (should be re-aliased rather than throwing an error) -->
        <xsl:element name="xml:foo" namespace="http://new-xml">
            <xsl:element name="xmlaa:foo" namespace="http://new-xml">
                <xsl:attribute name="xml:foo" namespace="http://new-xml2"/>
                <xsl:attribute name="xmlbb:foo" namespace="http://new-xml3"/>
            </xsl:element>
        </xsl:element>

        <!-- Name of element is 'xmlns' -->
        <xsl:element name="xmlns" namespace="http://my.com"/>

    </xsl:element>
</html>
