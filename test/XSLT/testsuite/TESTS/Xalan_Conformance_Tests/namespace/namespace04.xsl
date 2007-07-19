<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
  xmlns:bogus="http://bogus">

  <!-- FileName: namespace04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Test that default namespaces do not apply directly to attributes. -->

<xsl:template match="*[@up]">
  <foo/>
</xsl:template>

<xsl:template match="*[@bogus:up]">
  <!-- this template should not trigger because the element is in the "bogus" namespace,
       but its "up" attribute isn't -->
  <ERROR/>
</xsl:template>

</xsl:stylesheet>

