<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: whitespace35 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 3.4 -->
  <!-- Creator: Maynard Demmons (maynard@organic.com) -->
  <!-- Purpose: Test for whitespace stripping from source documents retrieved
                with the document() function. The spec is a little vague on this. -->
  <!-- Elaboration: doc/* would contain several whitespace nodes if not stripped.
       The built-in template for text would cause them to be emitted. -->

<xsl:strip-space elements="*" />

<xsl:template match="/">
  <out>
    <xsl:apply-templates/>
    <xsl:apply-templates select="document('docws35.xml')/doc"/>
  </out>
</xsl:template>

<xsl:template match="element">
  <xsl:element name="{(.)}"/>
</xsl:template>

</xsl:stylesheet>