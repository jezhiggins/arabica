<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP03 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disabling Output Escaping -->
  <!-- Purpose: Test for disabling output escaping in xsl:text -->

<xsl:template match="/">
  <HTML>
    <BODY>
      <xsl:text disable-output-escaping="yes"><![CDATA[<P>&nbsp;</P>]]></xsl:text>
    </BODY>
  </HTML>
</xsl:template>

</xsl:stylesheet>
