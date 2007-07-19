<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

  <!-- FileName: OUTP09 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disable Output Escaping -->
  <!-- Purpose: Test for disabling output 
       escaping in a variable with xsl:text, HTML output -->

<xsl:template match="/">
  <xsl:variable name="foo">
    <xsl:text disable-output-escaping="yes">&#064; &#126; &#033; &#043;</xsl:text>
    <xsl:text disable-output-escaping="no">&#064; &#126; &#033; &#043;</xsl:text>
  </xsl:variable>
  <HTML>
    <BODY>
      <xsl:copy-of select="$foo"/>
    </BODY>
  </HTML>
</xsl:template>

</xsl:stylesheet>
