<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon">

<!-- Written by Tom Amiro -->
  <!-- FileName: ac137.xsl -->
  <!-- Document: http://www.w3.org/TR/xslt11 -->
  <!-- DocVersion: 200001212 -->
  <!-- Section: 14 Extensions -->
  <!-- Purpose: Using element-available function to test for vendor extensions  -->

<xsl:template match="/">
<out>
  <xsl:if test="element-available('saxon:entity-ref')">
    <saxon:entity-ref name="nbsp" />
  </xsl:if>
  <xsl:if test="element-available('saxon:entity-ref') = false">
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:if>
</out>
</xsl:template>

</xsl:stylesheet>
