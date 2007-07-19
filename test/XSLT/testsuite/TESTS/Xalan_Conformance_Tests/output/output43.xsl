<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" cdata-section-elements="test"/>

  <!-- FileName: outp43 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Test of cdata-section-elements processing. <example>
  	   should not be processed.  -->

<xsl:template match="/">
  <out>
	<example>&gt;&gt;&gt;SHOULD NOT BE WRAPPED WITH cdata section&lt;&lt;&lt;</example><xsl:text>&#010;</xsl:text>
	<test>&gt;&gt;&gt;SHOULD BE WRAPPED WITH cdata section&lt;&lt;&lt;</test>
  </out>
</xsl:template>
 
</xsl:stylesheet>
