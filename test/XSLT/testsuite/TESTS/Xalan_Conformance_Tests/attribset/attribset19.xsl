<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: attribset19 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 7.1.3 Creating Attributes -->
  <!-- Creator: Paul Dick -->
  <!-- Purpose: Verify adding an attribute to an element after children
       have been added to it is an error. The attributes can be ignored.-->

<xsl:template match="doc">
   <Out>
      <xsl:element name="Element1">
   	     <xsl:attribute name="Att1">OK</xsl:attribute>
   	  </xsl:element>	  
   	  <xsl:attribute name="Att1">Wrong</xsl:attribute>
   	  <xsl:attribute name="Att1">Still-Wrong</xsl:attribute>
   </Out>
</xsl:template>

</xsl:stylesheet>