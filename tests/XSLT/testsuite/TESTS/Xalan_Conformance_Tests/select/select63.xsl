<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select63 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: test union operator used three times in an expression -->
  <!-- Creator: Carmelo Montanez --><!-- Expression023 in NIST suite -->

<xsl:template match = "doc">
  <out>
    <xsl:for-each select = "//child5|//child2|//child4">
      <xsl:value-of select="."/>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>