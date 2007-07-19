<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="urn:foo">


<xsl:template match="/">
   <xsl:element name="e1"><xsl:value-of select="$foo"/></xsl:element>
</xsl:template>

<xsl:variable name="foo" select="'var(foo)'"/>
<xsl:include href="test1.xsl"/>

</xsl:stylesheet>