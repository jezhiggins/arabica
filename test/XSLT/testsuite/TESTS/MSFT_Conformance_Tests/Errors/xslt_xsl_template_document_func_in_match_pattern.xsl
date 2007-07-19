<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MATCHerr06 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 12.1 Multiple Source Documents -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test document() function in a match pattern.
     The spec doesn't say whether it's allowed or not, but NOT seems likely. -->
  <!-- ExpectedException: Unknown nodetype: document -->

<xsl:template match="defaultcontent">
  <out>
    <xsl:apply-templates/>
  </out>
</xsl:template>

<xsl:template match="document('test.xml')//body">
  <xsl:value-of select="name(..)"/>
</xsl:template>

</xsl:stylesheet>