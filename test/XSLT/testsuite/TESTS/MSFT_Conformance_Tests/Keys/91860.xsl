<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
    <xsl:apply-templates select="//@*"/>
</xsl:template>

<xsl:template match="key('x','Redmond')">
        Element Name : <xsl:value-of select='name(.)'/>  ;
        NodeValue : <xsl:value-of select='.'/>  ;
        parentNodeName :  <xsl:value-of select="name(..)"/> ;
        grandParentNodeName:  <xsl:value-of select="name(../..)"/> ;  //expecting '<doc/>'
</xsl:template>

<xsl:key name="x" match="@att" use="text()"/>

</xsl:stylesheet>
