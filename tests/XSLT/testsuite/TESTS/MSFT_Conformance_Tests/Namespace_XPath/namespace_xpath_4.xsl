<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- Use default namespace from xsl file (should not find it) -->
  <xsl:template match="AAA" xmlns="ns1">
    <xsl:element name="AAA"/>
  </xsl:template>

  <!-- Use default namespace from xml file (should find it) -->
  <xsl:template match="p0:DDD" xmlns:p0="ns0">
    <xsl:element name="DDD"/>
  </xsl:template>

  <!-- Avoid extraneous whitespace -->
  <xsl:template match="text()"/>

</xsl:stylesheet>