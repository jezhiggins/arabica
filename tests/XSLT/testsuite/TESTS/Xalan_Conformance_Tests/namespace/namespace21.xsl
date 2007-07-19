<?xml version="1.0"?>
<xsl:stylesheet
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
   xmlns:em="http://www.psol.com/xtension/1.0"
   xmlns="http://www.w3.org/TR/REC-html40">

<!-- FileName: namespace21-->
<!-- Document: http://www.w3.org/TR/xpath -->
<!-- DocVersion: 19991116 -->
<!-- Section: Namespace Test  -->
<!-- Creator: Paul Dick -->
<!-- Purpose: Match namespace between stylesheet, in a select, and input.
     Prefixes differ but the URIs are the same. -->

<xsl:template match = "doc">
  <out>
    <xsl:for-each select="em:foo">
      <xsl:value-of select="."/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>
