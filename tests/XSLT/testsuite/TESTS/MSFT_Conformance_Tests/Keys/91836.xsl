<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
>
<xsl:output method="xml" omit-xml-declaration="yes"/>

<!-- indixing entity node -->

<xsl:template match="/" >
    <xsl:apply-templates select="key('foo','Redmond')"/>
</xsl:template>

<xsl:template match="key('foo','Redmond')">
    <xsl:value-of select='./@name'/> : <xsl:value-of select='.'/> : <xsl:value-of select="name(..)"/>;
</xsl:template>

<xsl:key name="foo" match="city" use="@name"/>
<xsl:key name="foo" match="a" use="@att"/>
<xsl:key name="foo" match="a" use="@att1"/>
<xsl:key name="foo" match="a" use="@att2"/>
<xsl:key name="foo" match="a" use="@att3"/>

<xsl:key name="foo" match="b" use="@att"/>

</xsl:stylesheet>
