<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: namespace42 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.2 Creating Elements -->
  <!-- Creator: Scott Boag -->
  <!-- Purpose: Test to make sure xsl:attribute isn't added to the containing 
       element when an xsl:element is ignored. Should see a warning that xyz:foo 
       was not created.	The <yyy/> element is placed directly within out, but the 
       attribute isn't. -->

<xsl:template match = "/">
  <out>
    <xsl:element name="xyz:foo">
      <xsl:attribute name="baz"/>
      <yyy/>
    </xsl:element>
  </out>
</xsl:template>

</xsl:stylesheet>


