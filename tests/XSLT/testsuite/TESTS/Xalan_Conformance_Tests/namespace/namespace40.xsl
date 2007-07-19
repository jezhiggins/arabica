<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace40 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Discretionary: name="element-name-not-QName" choice="pass-through" -->
  <!-- Creator: Scott Boag -->
  <!-- Purpose: Test for resetting of a prefixed namespace by a LRE. -->
  <!-- Should see one warning about namespace "none" unresolvable.
       Recovery: put yyy directly inside higher element (out). -->

<xsl:template match = "/">
  <out>
    <xsl:element name="none:foo">
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>