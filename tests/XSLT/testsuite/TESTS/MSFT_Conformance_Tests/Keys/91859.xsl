<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>
<xsl:output method="xml" omit-xml-declaration="yes"/>
<!-- indixing entity node -->


<xsl:template match="/" >
    <xsl:apply-templates select="//@*"/>
    <xsl:apply-templates select="key('bar','Redmond')"/>
</xsl:template>

<xsl:template match="@*">
</xsl:template>

<!-- WHY there is no match for 'att3' which has 'Redmond' as value??-->
<xsl:template match="key('foo', 'Redmond')">
    TESTING
    : <xsl:value-of select='name(.)'/>  ;
    : <xsl:value-of select='name(..)'/>  ;
</xsl:template>

<!-- this one match, meaning the PE references work in att3-->
<xsl:template match="key('bar', 'Redmond')">
    Element Name : <xsl:value-of select='name(.)'/>  ;
    NodeValue : <xsl:value-of select='.'/>  ;
</xsl:template>

<!-- note that attribute has no text() in xpath tree logic-->
<xsl:key name="foo" match="@att" use="."/>
<xsl:key name="foo" match="@att1" use="."/>

<xsl:key name="bar" match="a" use="@att3"/>

</xsl:stylesheet>
