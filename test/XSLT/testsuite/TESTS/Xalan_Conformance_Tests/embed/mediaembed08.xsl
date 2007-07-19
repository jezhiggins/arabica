<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: EMBED08 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.7 Embedding Stylesheets. -->
  <!-- Purpose: Test the media attribute and -MEDIA command-line option -->

<xsl:key name="test" match="para" use="@id"/>

  <xsl:template match="/">
	<out>
    <xsl:value-of select="doc/body/para"/>
    <xsl:value-of select="key('test','foey')"/>
	</out>
  </xsl:template>
</xsl:stylesheet>