<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: select14 -->
  <!-- Document: http://www.w3.org/TR/Xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.3 Node Sets -->
  <!-- Purpose: Node-set union using mixed axes --><!-- Expression013 in NIST suite -->
  <!-- Creator: Carmelo Montanez, adapted by David Marston -->

<xsl:template match="/doc/sub1/child2">
  <out>
    <xsl:for-each select="preceding-sibling::child1|//child3">
      <xsl:value-of select="."/><xsl:text>
</xsl:text>
    </xsl:for-each>
  </out>
</xsl:template>

<xsl:template match="text()"/><!-- To suppress other output -->

</xsl:stylesheet>