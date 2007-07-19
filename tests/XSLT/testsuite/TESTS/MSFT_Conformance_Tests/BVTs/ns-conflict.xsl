<!-- UTF-8 -->
<!-- Use default namespace.  Don't output XSL namespace -->
<html xml:space="default" xmlns="urn:xhtml" xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:text>&#10;</xsl:text>

    <!-- Cause conflict between generated global attribute with empty prefix & local attribute -->
    <foo:p xmlns:foo="http://my.com">
        <xsl:attribute name="attr" namespace="http://my.com.2"/>
    </foo:p><xsl:text>&#10;</xsl:text>

    <!-- Use auto-generated name explicitly -->
    <auto-ns1:p xmlns:auto-ns1="urn:xhtml">
        <xsl:attribute name="auto-ns1:attr" xmlns:auto-ns1="urn:another"/>
        <xsl:attribute name="auto-ns1:attr2" xmlns:auto-ns1="urn:another"/>
    </auto-ns1:p><xsl:text>&#10;</xsl:text>

    <!-- Override default namespace with null namespace.  Cause multiple conflicts. -->
    <p xmlns="" xmlns:auto-ns2="urn:cause-conflict" xmlns:auto-ns3="urn:cause-conflict-again">
        <xsl:attribute name="auto-ns1:attr" xmlns:auto-ns1="urn:another"/>
        <xsl:attribute name="auto-ns2:attr2" xmlns:auto-ns2="urn:another"/>
        <xsl:attribute name="auto-ns2:attr3" xmlns:auto-ns2="urn:another"/>
    </p><xsl:text>&#10;</xsl:text>

    <!-- Element's prefix is defined in higher scope -->
    <p xmlns:foo="urn:foo"><xsl:text>&#10;</xsl:text>
        <foo:p>
            <xsl:attribute name="foo:attr" xmlns:foo="urn:foo2"/>
        </foo:p><xsl:text>&#10;</xsl:text>
    </p><xsl:text>&#10;</xsl:text>

    <!-- Attribute's prefix is defined in higher scope -->
    <p xmlns:foo="urn:foo"><xsl:text>&#10;</xsl:text>
        <p foo:attr="val">
            <xsl:attribute name="foo:attr" xmlns:foo="urn:foo2"/>
        </p><xsl:text>&#10;</xsl:text>
    </p><xsl:text>&#10;</xsl:text>

</html>
