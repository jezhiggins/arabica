<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ext="http://somebody.elses.extension"
                extension-element-prefixes="ext">

  <!-- FileName: EXTEND04 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 15 Fallback -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test for-each inside xsl:fallback. Also have content with in
       the extension. -->

<xsl:template match="doc">
  <out>
    <ext:test>
	  <xsl:call-template name="oops">
	    <xsl:with-param name="oopsdata" select="'Gadzookz'"/>
	  </xsl:call-template>
      <xsl:fallback>
        <xsl:for-each select="a">
          <xsl:value-of select="."/>
        </xsl:for-each>
      </xsl:fallback>
    </ext:test>
  </out>
</xsl:template>

<xsl:template name="oops">
   <xsl:param name="oopsdata" select="'default'"/>
   <xsl:value-of select="$oopsdata"/>
</xsl:template>

</xsl:stylesheet>