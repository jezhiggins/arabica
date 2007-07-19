<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disable Output Escaping -->
  <!-- Purpose: Test for enabling output escaping in xsl:text, HTML output -->

<xsl:template match="/">
  <HTML>
    <BODY>
      <P><xsl:text disable-output-escaping="no"><![CDATA[<P>&nbsp;</P>]]></xsl:text></P>
      <P><xsl:text disable-output-escaping="yes"><![CDATA[<P>&nbsp;</P>]]></xsl:text></P>
    </BODY>
  </HTML>
</xsl:template>

</xsl:stylesheet>
