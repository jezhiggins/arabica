<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: outp67 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: Verify standalone attribute set to "yes". -->

<xsl:output method="xml" standalone="yes"/>

<xsl:template match="doc">
	<root>
		<xsl:value-of select="node"/>
	</root>
</xsl:template>

</xsl:stylesheet>