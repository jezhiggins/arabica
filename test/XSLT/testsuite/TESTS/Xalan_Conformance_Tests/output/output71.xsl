<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: OUTP71 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 -->
  <!-- Purpose: Test that implied HTML output assumes indent=yes. -->

<xsl:template match="/">
<HTML>
  <BODY>
    <out>
      <xsl:value-of select="doc/foo"/>
    </out>
  </BODY>
</HTML>
</xsl:template>

</xsl:stylesheet>
