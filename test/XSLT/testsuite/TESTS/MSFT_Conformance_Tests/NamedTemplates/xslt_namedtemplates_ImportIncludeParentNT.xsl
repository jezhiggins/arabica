<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:import href="xslt_namedtemplates_ImportIncludeParentNT1.xsl" />

  <xsl:output omit-xml-declaration="yes" encoding="utf-8" />

  <xsl:template match='/'>
	<xsl:call-template name="Foo" />
  </xsl:template>

  <xsl:template name="Bar">
	<Bar>Bar Stylesheet 1</Bar>
  </xsl:template>

</xsl:stylesheet>