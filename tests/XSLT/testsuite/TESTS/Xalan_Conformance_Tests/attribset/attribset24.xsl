<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
            xmlns:bdd="http://bdd.test.com">

  <!-- FileName: attribset24 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: The attribute must be in the designated namespace, even if the prefix has
    to be reset or ignored. -->

<xsl:template match="/">
  <out>
    <jam>
      <xsl:attribute name="{docs/b}" namespace="http://xyz.com">jaminben</xsl:attribute>
    </jam>
  </out>
</xsl:template>

</xsl:stylesheet>