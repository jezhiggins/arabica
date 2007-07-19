<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset36 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Verify adding an attribute to an element after a comment has
       been added to it is an error. The attributes can be ignored.
       The spec doesn't explicitly say this is disallowed, as it does
       for child elements, but it makes sense to have the same treatment. -->

<xsl:template match="doc">
  <Out>
    <xsl:element name="Element1">
      <xsl:attribute name="Att1">OK</xsl:attribute>
      <xsl:comment>Should not break</xsl:comment>
      <xsl:attribute name="AttX">Wrong</xsl:attribute>
      <xsl:element name="Element2"/>
    </xsl:element>
  </Out>
</xsl:template>

</xsl:stylesheet>