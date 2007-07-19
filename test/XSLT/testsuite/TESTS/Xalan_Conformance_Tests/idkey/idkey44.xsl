<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey44 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test simple key()// filtered by a predicate, in a match pattern. -->


<xsl:key name="Info" match="Level3" use="@ID"/>

<xsl:template match="/">
 <out>
	<xsl:apply-templates select="//Level3"/>
 </out>
</xsl:template>


<xsl:template match="key('Info','id15')//Level3[Name[starts-with(@First,'J')]]">
	<xsl:text>&#10;</xsl:text>
	<xsl:element name="J-Name">
		<xsl:value-of select="Name/@First"/>
	</xsl:element>
</xsl:template>

<xsl:template match="*">
	<xsl:text>&#10;</xsl:text>
	<xsl:element name="Name">
		<xsl:value-of select="Name/@First"/>
	</xsl:element>
</xsl:template>

</xsl:stylesheet>