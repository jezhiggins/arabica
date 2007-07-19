<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: outp72 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.3 Creating Processing Instructions. -->
  <!-- Purpose: Test the generation of Processing instructions. -->

<xsl:template match="doc/tag">
<out>
  <?PI1 Dothis ?>
  <?PI2 Dothat ?>
  <xsl:processing-instruction name="my-pi">href="book.css" type="text/css"</xsl:processing-instruction>
  <xsl:processing-instruction name="mytag">
	<xsl:value-of select="."/>
	 ?>
  </xsl:processing-instruction>
</out>
</xsl:template>
 
</xsl:stylesheet>