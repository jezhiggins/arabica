<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: variable53 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.6 -->
  <!-- Author: John Howard -->
  <!-- Purpose: test using recursion to traverse a node-set in a variable. -->
 
<xsl:output method="xml"/>

<xsl:template match="/">
  <out>
    <xsl:call-template name="traverse-vals">
      <xsl:with-param name="pos" select="1"/>
    </xsl:call-template>
  </out>
</xsl:template>

<xsl:template name="traverse-vals">
  <xsl:param name="pos"/>
  <xsl:variable name="series" select="/data/*/datum/@value"/>

  <xsl:value-of select="concat($series[number($pos)],' ')"/>
  <xsl:if test="$pos &lt; count($series)">
    <xsl:call-template name="traverse-vals">
      <xsl:with-param name="pos" select="$pos + 1"/>
    </xsl:call-template>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>