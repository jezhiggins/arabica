<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:output method="html" encoding="SHIFT_JIS"/>

  <!-- FileName: OUTP73 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.2 HTML Output Method -->
  <!-- Purpose: Test SHIFT_JIS encoding on HTML output.-->

<xsl:template match="/">
  <HTML>
    <HEAD></HEAD>
    <body>Hiragana &#x3041; &#x3051; &#x3061; &#x3071; &#x3081; &#x3091;</body>
  </HTML>
</xsl:template>

</xsl:stylesheet>
