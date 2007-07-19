<?xml version='1.0'?>

<!-- This is a regression test for bug 49668. It is a stylesheet, with another
included stylesheet that uses toplevel xsl elements without an xsl namespace -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:output omit-xml-declaration="yes" />

  <xsl:template match="/">

    <span style="color=green">
    Include file with literal result element 
    </span>
    <p/>  
          
      <xsl:for-each select="//book/author">
      <span style="color=blue" ID="test"> <xsl:value-of select="award"/> </span>
      </xsl:for-each>

  </xsl:template>

  <xsl:include href="xslt_include_IncludedNSSecond.xsl"/>

</xsl:stylesheet>
