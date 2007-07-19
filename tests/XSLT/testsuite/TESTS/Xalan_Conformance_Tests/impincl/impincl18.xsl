<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!-- FileName: impincl18 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.6 Overriding Template Rules -->
  <!-- Creator: Gary L Peskin -->
  <!-- Purpose: When no stylesheets are imported, an xsl:apply-imports should
       select the built-in templates. -->

<xsl:template match="/">
  <xsl:message>This message should be issued only one time.</xsl:message>
  <result>
    Before apply-imports
      <xsl:apply-imports/>
    After apply-imports
  </result>
</xsl:template>

</xsl:stylesheet>
