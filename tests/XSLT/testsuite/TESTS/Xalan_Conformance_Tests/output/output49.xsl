<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP49 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: HTML output method should not escape '<' in attribute values. -->

<xsl:template match="/">
  <HTML>
    <foo name="&lt;abcd>"/>
	<h1 title="&lt;contacts>">People</h1>
	<frame name="z&lt;this>z"/>    
  </HTML>
</xsl:template>

</xsl:stylesheet>
