<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ext="http://somebody.elses.extension"
                extension-element-prefixes="ext">

  <!-- FileName: extend02 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 15 Fallback -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Testing that xsl:fallback engages when required. -->

  <xsl:template match="/">
    <out>
      <ext:test>
        <xsl:fallback>
          <xsl:text>Fallback: extension was not found.</xsl:text>
        </xsl:fallback>
      </ext:test>
    </out>
  </xsl:template>

</xsl:stylesheet>