<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes"/>

  <!-- FileName: OUTP45 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.1 XML Output Method -->
  <!-- Purpose: xml method should not output XML declaration if 
     omit-xml-declaration="yes". -->

<xsl:template match="/">
  <example>SHOULD NOT have XML Declaration</example>
</xsl:template>
 
</xsl:stylesheet>
