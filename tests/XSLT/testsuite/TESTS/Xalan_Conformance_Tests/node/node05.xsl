<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:baz1="http://xsl.lotus.com/ns1"
                xmlns:baz2="http://xsl.lotus.com/ns2">

  <!-- FileName: node05 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 4.1 Node Set Functions  -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test of 'namespace-uri()'  -->

<xsl:template match="baz2:doc">
  <out>
    <xsl:value-of select="namespace-uri(*)"/>
  </out>
</xsl:template>

</xsl:stylesheet>
