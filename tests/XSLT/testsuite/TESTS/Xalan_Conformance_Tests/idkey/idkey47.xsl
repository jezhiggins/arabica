<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey47 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test complex key()//x/x in match pattern. -->


<xsl:key name="Info" match="Level1 | Level2 | Level3" use="@ID"/>

<xsl:template match="/">
 <out>
	<xsl:apply-templates select="//Level3"/>
 </out>
</xsl:template>

<xsl:template match="key('Info','id1')//Level3/Level3">
	<xsl:text>&#10;</xsl:text>
	<xsl:element name="Simple-Match">
		<xsl:value-of select="Name/@First"/>
	</xsl:element>
</xsl:template>


<xsl:template match="*">
	<xsl:text>&#10;</xsl:text>
	<xsl:element name="No-Match">
		<xsl:value-of select="Name/@First"/>
	</xsl:element>
</xsl:template>

</xsl:stylesheet>