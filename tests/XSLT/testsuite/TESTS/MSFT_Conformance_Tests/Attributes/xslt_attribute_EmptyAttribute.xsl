<!-- This test matches the child element Item1 beneath the root, and applies an attribute of
name equals NULL -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output omit-xml-declaration="yes" />

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>


  <xsl:template match="Item1">
	<xsl:element name="result">

	<xsl:attribute name="" />
	</xsl:element>

  </xsl:template>

</xsl:stylesheet>