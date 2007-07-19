<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:include href="xslt_attributeset_ImportSamePrec1.xsl" />

  <xsl:output omit-xml-declaration="yes" encoding="utf-8" />


  <xsl:template match='/'>
	<foo xsl:use-attribute-sets="foobar">text</foo>
  </xsl:template>

  <xsl:attribute-set name="foobar">
	<xsl:attribute name="big">dog</xsl:attribute>
	<xsl:attribute name="small">cat</xsl:attribute>
  </xsl:attribute-set>

</xsl:stylesheet>