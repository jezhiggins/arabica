<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" cdata-section-elements="example"/>

  <!-- FileName: OUTP41 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Text node containing "]]>" and closure of CDATA section. -->

<xsl:template match="/">
	<example>]]&gt;</example>
</xsl:template>

</xsl:stylesheet>
