<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- Use same query multiple times, with different namespace in scope -->
  <xsl:template match="p1:*" xmlns:p1="ns_root">
    <xsl:for-each select="p1:*" xmlns:p1="ns1">
        <xsl:copy-of select="p1:*" xmlns:p1="ns2"/>
    	<xsl:apply-templates/>
    </xsl:for-each>
  </xsl:template>

  <xsl:template match="p1:*" xmlns:p1="ns3">
    <xsl:copy/>
  </xsl:template>

  <!-- Avoid extraneous whitespace -->
  <xsl:template match="text()"/>

</xsl:stylesheet>