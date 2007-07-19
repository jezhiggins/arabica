<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Test for STYLE handling -->

<xsl:template match="/">
  <HTML>
    <HEAD>
      <STYLE>
        <![CDATA[
        <>&
        ]]>
      </STYLE>
    </HEAD>
    <BODY/>
  </HTML>
</xsl:template>

</xsl:stylesheet>
