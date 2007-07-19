<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:output omit-xml-declaration="yes" encoding="utf-8" />

  <xsl:include href="xslt_namedtemplates_IncludeSameNamePrec.xsl" />


  <xsl:template match='/'>
	<xsl:call-template name="Foo" />
  </xsl:template>

  <xsl:template name="Foo">
	<Foo>Foo StyleSheet 1</Foo>
  </xsl:template>

</xsl:stylesheet>