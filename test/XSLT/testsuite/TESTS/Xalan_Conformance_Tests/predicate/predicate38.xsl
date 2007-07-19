<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" indent="yes"/>

  <!-- FileName: predicate38 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Purpose: Stress test of nested and multiple predicates. The production rules
       allow such nesting. -->
  <!-- Author: Paul Dick -->

<xsl:template match="doc">
<out>
  <predicate1>
   <xsl:apply-templates select="foo[(bar[2])='this']"/>
  </predicate1>
  <predicate2>
   <xsl:apply-templates select="foo[(bar[2][(baz[2])='goodbye'])]"/>
  </predicate2>
</out>
</xsl:template>

<xsl:template match="foo[(bar[2])='this']">
 <xsl:text>1 is </xsl:text>	<xsl:for-each select="*">
    	<xsl:value-of select="@attr"/><xsl:text>,</xsl:text>
	</xsl:for-each>
</xsl:template>

<xsl:template match="foo[(bar[(baz[2])='goodbye'])]">
 <xsl:text>3 is </xsl:text>	<xsl:for-each select="*">
    	<xsl:value-of select="@attr"/><xsl:text>,</xsl:text>
	</xsl:for-each>
</xsl:template>

<xsl:template match="foo[(bar[2][(baz[2])='goodbye'])]">
 <xsl:text>2 is </xsl:text>	<xsl:for-each select="*">
    	<xsl:value-of select="@attr"/><xsl:text>,</xsl:text>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>