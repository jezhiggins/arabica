<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset43 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.4 Named Attribute Sets -->
  <!-- Creator: David Marston, based on a test by Morten Jorgensen -->
  <!-- Purpose: Test inheritance of attribute sets. A xsl:element instruction
                is referring an attribute set that is defined by two separate
                xsl:attribute-set elements with the same name. -->

<xsl:output indent="yes"/>

<xsl:template match="/">
  <xsl:element name="out" use-attribute-sets="child">
    <xsl:attribute name="location">Wonderland</xsl:attribute>
  </xsl:element>
</xsl:template>

<xsl:attribute-set name="child">
  <xsl:attribute name="follow">yellowbrickroad</xsl:attribute>
  <xsl:attribute name="rabbithole">shallow</xsl:attribute>
</xsl:attribute-set>

<xsl:attribute-set name="child">
  <xsl:attribute name="follow">theleader</xsl:attribute>
  <xsl:attribute name="alice">intoxicated</xsl:attribute>
</xsl:attribute-set>

</xsl:stylesheet>