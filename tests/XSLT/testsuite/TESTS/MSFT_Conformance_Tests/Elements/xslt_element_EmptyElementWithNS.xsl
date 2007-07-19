<!-- This test matches the child element Item1 beneath the root, replaces that element with a new
element of name equal to value NULL but uses a valid namespace -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output omit-xml-declaration="yes" />

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>


  <xsl:template match="Item1">
	<xsl:element name="" namespace="ns1"/>
  </xsl:template>

</xsl:stylesheet>