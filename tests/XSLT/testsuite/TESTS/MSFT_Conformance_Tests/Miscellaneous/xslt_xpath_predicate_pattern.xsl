<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="doc">
  <out>
  <xsl:for-each select = "a[1 &lt; 2 &lt; 3]">
    <xsl:value-of select="."/>
    <!-- Always true; (1 &lt; 2 ) converts to true; true converts to 1; and (1 &lt; 3) is true. -->
  </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>