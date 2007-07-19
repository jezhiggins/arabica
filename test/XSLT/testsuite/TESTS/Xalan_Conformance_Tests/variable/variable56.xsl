<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: variable56 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 11.5 -->
  <!-- Author: darrylf@schemasoft.com -->
  <!-- Purpose: Use same-named variables in inner and outer scopes, where inner is a for-each loop. -->
  <!-- This may need to become an error case. -->
 
<xsl:output method="xml" indent="yes" />

<xsl:template match="/">
  <xsl:variable name="bar">outer</xsl:variable>
  <outer bar="{$bar}">
    <xsl:for-each select="./*">
      <xsl:variable name="bar">inner</xsl:variable>
      <inner bar="{$bar}"/>
    </xsl:for-each>
  </outer>
</xsl:template>
                
</xsl:stylesheet>