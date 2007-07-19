<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ext="http://somebody.elses.extension"
                extension-element-prefixes="ext">

  <!-- FileName: Message15 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 13 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test xsl:fallback inside xsl:message -->

<xsl:template match="docs">
  <out>
    <xsl:message>
      <xsl:text>Message from MESSAGE15: </xsl:text>
      <ext:test>
        <xsl:fallback>We got inside</xsl:fallback>
      </ext:test>
    </xsl:message>
  </out>
</xsl:template>

</xsl:stylesheet>
