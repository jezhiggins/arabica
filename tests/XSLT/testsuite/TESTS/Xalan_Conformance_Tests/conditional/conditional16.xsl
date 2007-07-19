<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: conditional16 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 9.1 -->
  <!-- Purpose: Test of compound conditions within xsl:if. -->

<xsl:template match="Family">
  <out>
    <xsl:for-each select="*">  
      <xsl:if test="@name='John'or @name='Joe'">
      <xsl:value-of select="@name"/> Smith</xsl:if><xsl:text>
</xsl:text>  
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>