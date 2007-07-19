<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
                xmlns:foo="http://foo.com">

  <!-- FileName: namedtemplate05 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 6 Named Templates -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Call named template with non-qualified name, but with 
       qualified name in scope. -->

<xsl:template match="doc">
  <out>
    <xsl:call-template name="a"/>
  </out>
</xsl:template>

<xsl:template name="foo:a">
  foo:a
</xsl:template>

<xsl:template name="a">
  a
</xsl:template>

</xsl:stylesheet>
