<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- FileName: select85 -->
<!-- Document: http://www.w3.org/TR/xslt -->
<!-- DocVersion: 19991116 -->
<!-- Section: 12.4 Miscellaneous Additional Functions -->
<!-- Purpose: Test current() by itself in a predicate. -->
<!-- Creator: Henry Zongaro -->

<xsl:output method="xml" indent="no" encoding="UTF-8"/>

<xsl:template match="doc">
  <out>
    <xsl:text>&#10;</xsl:text>
    <xsl:apply-templates select="mark"/>
    <xsl:text>&#10;</xsl:text>
  </out>
</xsl:template>

<!-- Both of the following should select the same thing. -->
<xsl:template match="mark">
  <in><xsl:value-of select="following-sibling::ch[current()]"/></in>
  <xsl:text>&#10;</xsl:text>
  <in><xsl:value-of select="(following-sibling::ch[current()])[1]"/></in>
</xsl:template>

</xsl:stylesheet>