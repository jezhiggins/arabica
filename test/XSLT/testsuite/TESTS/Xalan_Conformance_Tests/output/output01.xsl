<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <!-- FileName: OUTP01 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Test for SCRIPT handling -->

<xsl:template match="/">
  <HTML>
    <HEAD>
      <SCRIPT>
        <![CDATA[
        document.write("<P>Hi Oren");
        if((2 < 5) & (6 < 3))
        {
          ...
        }
        ]]>
      </SCRIPT>
    </HEAD>
    <BODY/>
  </HTML>
</xsl:template>

</xsl:stylesheet>
