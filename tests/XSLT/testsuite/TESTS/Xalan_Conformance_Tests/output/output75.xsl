<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml"/>

  <!-- FileName: output75 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disable output escaping. -->
  <!-- Purpose: Spec states:It is an error for output escaping to be disabled 
       for a text node that is used for something other than a text node in the 
       result tree. Thus, it is an error to disable output escaping for an 
       xsl:value-of or xsl:text element that is used to generate the string-value 
       of a comment, processing instruction or attribute node; OUTPUT = XML  -->
  <!-- Author: Paul Dick -->

<xsl:template match="doc">
 <xml><xsl:text>&#10;</xsl:text>
  <out1>
	<xsl:attribute name="attrib1">
		<xsl:text disable-output-escaping="no">_&lt;Whoa-No&gt;_</xsl:text>
	</xsl:attribute>
	<xsl:attribute name="attrib2">
		<xsl:value-of select="a" disable-output-escaping="no"/>
	</xsl:attribute></out1><xsl:text>&#10;</xsl:text>

  <!-- This is the error case. It should come out as d-o-e="no" -->
  <out2>
	<xsl:attribute name="attrib3">
		<xsl:text disable-output-escaping="yes">_&lt;Whoa-Yes&gt;_</xsl:text>
	</xsl:attribute>
	<xsl:attribute name="attrib4">
		<xsl:value-of select="a" disable-output-escaping="yes"/>
	</xsl:attribute></out2><xsl:text>&#10;</xsl:text>

  <out3>
	<xsl:value-of select="a" disable-output-escaping="yes"/>
  </out3><xsl:text>&#10;</xsl:text>
 </xml>
</xsl:template>
 
</xsl:stylesheet>
