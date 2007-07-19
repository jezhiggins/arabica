<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- XPath should not return any xmlns attributes, since these are considered namespace nodes -->
  <xsl:template match="*">
    <xsl:for-each select="@xmlns | @xmlns:*">
        <xsl:element name="x{name(.)}">
	    <xsl:value-of select="."/>
	</xsl:element>
    </xsl:for-each>
    <xsl:apply-templates/>
  </xsl:template>

  <!-- Avoid extraneous whitespace -->
  <xsl:template match="text()"/>

</xsl:stylesheet>