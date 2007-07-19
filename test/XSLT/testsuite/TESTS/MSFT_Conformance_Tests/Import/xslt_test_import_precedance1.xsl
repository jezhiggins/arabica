<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="urn:foo">
    <xsl:import href="test1.inc"/>
    <xsl:import href="test2.inc"/>


<xsl:template match="/">
   <xsl:element name="e1"><xsl:value-of select="$foo"/></xsl:element>
</xsl:template>


</xsl:stylesheet>