<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 

<!-- According to the spec, this should not give an error, since the scope of the embedded v3 extends only to its descendants and siblings. -->

<xsl:template match="/">
  <abc>
    <xsl:variable name="v3" select="'val'"/>
  </abc>
  <xsl:variable name="v3" select="'val'"/>
</xsl:template>

</xsl:stylesheet>