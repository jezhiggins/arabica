<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:baz="http://xsl.lotus.com/ns1"
                xmlns:bar="http://xsl.lotus.com/ns1"
                exclude-result-prefixes="bar baz">

  <!-- FileName: idkey53 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.2 -->
  <!-- Creator: David Bertoni -->
  <!-- Purpose: Test for xsl:key and key() with a qualified name, different prefix. -->

<xsl:output method="xml" encoding="UTF-8"/>

<xsl:key name="baz:mykey" match="div" use="title"/>

<xsl:template match="doc">
  <root>
    <xsl:value-of select="key('bar:mykey', 'Introduction')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('bar:mykey', 'Stylesheet Structure')/p"/><xsl:text> </xsl:text>
    <xsl:value-of select="key('bar:mykey', 'Expressions')/p"/>
  </root>
</xsl:template>

</xsl:stylesheet>
