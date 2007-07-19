<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace73 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Discretionary: name="element-name-not-QName" choice="pass-through" -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Put an unprefixed xmlns declaration in xsl:element where requested name has prefix. -->
  <!-- Should see one warning about namespace "abc" unresolvable.
       Recovery: put yyy directly inside higher element (out). -->

<xsl:template match = "/">
  <out>
    <xsl:element name="abc:foo" xmlns="">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>