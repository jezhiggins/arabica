<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace43 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Discretionary: name="element-name-not-QName" choice="pass-through" -->
  <!-- Creator: Scott Boag -->
  <!-- Purpose: Test for non-empty illegal element name. -->
  <!-- Should see a warning about illegal element name. Recovery: put yyy directly in out. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="this is a string">
      <yyy xmlns=""/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>