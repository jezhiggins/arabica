<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="text"/>

  <!-- FileName: output76 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 16.3 -->
  <!-- Purpose: Test for text output with special characters.  -->

<xsl:template match="/">
     <xsl:for-each select="doc/alpha">
         <xsl:value-of select="@key"/>@
     </xsl:for-each>
     <xsl:for-each select="doc/alpha">
         <xsl:value-of select="."/>-
     </xsl:for-each>
</xsl:template>

</xsl:stylesheet>