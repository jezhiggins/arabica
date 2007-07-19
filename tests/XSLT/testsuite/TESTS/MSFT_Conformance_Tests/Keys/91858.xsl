<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<!--
xsl:key : Index  &a;&b; as a node value,  Where &a;='a' and &b;='b'
-->

<xsl:template match="/">
    <xsl:for-each select="key('x', 'xxxabyyy')">
        THIS SHOULD WORK
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
    </xsl:for-each>

    <xsl:for-each select="key('x', 'xxx')">
        THIS SHOULD NOT WORK
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
    </xsl:for-each>

    <xsl:for-each select="key('x', 'yyy')">
        THIS SHOULD NOT WORK
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
    </xsl:for-each>

    <xsl:for-each select="key('x', 'a')">
        THIS SHOULD NOT WORK
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
    </xsl:for-each>

    <xsl:for-each select="key('x', 'b')">
        THIS SHOULD NOT WORK
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
    </xsl:for-each>
</xsl:template>

<xsl:key name="x" match="elem" use="text()"/>
<xsl:key name="y" match="elem" use="text()"/>
<xsl:key name="z" match="elem" use="text()"/>

</xsl:stylesheet>
