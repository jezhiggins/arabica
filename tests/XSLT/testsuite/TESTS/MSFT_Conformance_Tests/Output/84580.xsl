<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
<xsl:output method="xml" omit-xml-declaration="yes"/>

<xsl:template match="/">
  <xsl:element name="foo">
    <xsl:value-of select="'a'"/>
    <xsl:value-of select="'b'"/>
    <xsl:value-of select="'c'"/>
  </xsl:element>
</xsl:template>

</xsl:stylesheet>
