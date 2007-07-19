<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select41 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: NodeSet union using two absolute location paths--><!-- Expression001 in NIST suite -->
  <!-- Creator: Carmelo Montanez -->

<xsl:template match="/">
  <out><xsl:text>
</xsl:text>
    <xsl:apply-templates select = "/doc/sub1/child1|/doc/sub2/child2"/>
  </out>
</xsl:template>

<xsl:template match="*">
  <xsl:value-of select="."/><xsl:text>
    </xsl:text>
</xsl:template>

</xsl:stylesheet>