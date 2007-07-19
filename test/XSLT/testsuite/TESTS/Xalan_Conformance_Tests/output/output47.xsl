<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP47 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.4 Disabling Output Escaping -->
  <!-- Purpose: Illegal use of disable-output-escaping. -->

<xsl:template match="/">
  <out>
    <xsl:variable name="nodetext">
      <xsl:text disable-output-escaping="yes">This is &lt;b>BOLD1&lt;/b> text.</xsl:text>
    </xsl:variable>
    <xsl:value-of select="$nodetext"/>
  </out>
</xsl:template>

</xsl:stylesheet>
