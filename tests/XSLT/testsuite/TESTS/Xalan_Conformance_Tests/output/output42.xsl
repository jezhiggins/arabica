<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml" cdata-section-elements="example test"/>

  <!-- FileName: outp42 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Test of cdata-section-elements processing. -->

<xsl:template match="/">
  <out>
	<example>&lt;foo></example><xsl:text>&#010;</xsl:text>
	<example>&gt;&gt;&gt;HELLO&lt;&lt;&lt;</example><xsl:text>&#010;</xsl:text>
	<test><![CDATA[>>>HELLO<<<]]></test>
  </out>
</xsl:template>
 
</xsl:stylesheet>
