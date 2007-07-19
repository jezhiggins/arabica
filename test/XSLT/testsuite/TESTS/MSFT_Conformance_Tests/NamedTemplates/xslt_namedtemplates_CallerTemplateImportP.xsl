<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- This stylesheet is a regression test case for bug 65746. Validates
       correct import precedence of various top-level elements. -->

  <xsl:import href="xslt_namedtemplates_ExtraTemplateImportP.xsl" />

  <xsl:output omit-xml-declaration="yes" encoding="utf-8" />
  
  <xsl:template match='/'>
	<xsl:call-template name="Foo" />
        <xsl:call-template name="Bar" />
  </xsl:template>

  <xsl:template name="Foo">
        <Foo>Foo Stylesheet 1</Foo>
  </xsl:template>

</xsl:stylesheet>