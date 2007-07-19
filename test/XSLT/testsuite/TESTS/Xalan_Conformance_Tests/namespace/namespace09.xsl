<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:baz1="http://xsl.lotus.com/ns1"
                xmlns:baz2="http://xsl.lotus.com/ns2">

  <!-- FileName: namespace09 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 Node Set Functions. -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of 'local-name()' function on attribute in non-default namespace. -->

<xsl:template match="baz2:doc">
  <out>
    <xsl:value-of select="local-name(baz2:b/@baz1:attrib2)" xmlns:baz1="http://xsl.lotus.com/ns1" xmlns:baz2="http://xsl.lotus.com/ns2"/>
  </out>
</xsl:template>

</xsl:stylesheet>