<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Test for DCR 53329. -->

  <xsl:output method="xml" omit-xml-declaration="no" indent="no" encoding='utf-8' />  

  <xsl:template match="/">
    <bareroot>
	<litresult xsl:use-attribute-sets='foo'>foobar</litresult>
    </bareroot>
  </xsl:template>

  <xsl:attribute-set name='foo'>
     <xsl:attribute name='green-lantern'>
	<xsl:text disable-output-escaping='no'>&lt;lantern</xsl:text>
     </xsl:attribute>

     <xsl:attribute name='silver-surfer'>
	<xsl:text disable-output-escaping='yes'>"silver&quot; &lt; &gt; &apos;</xsl:text>
     </xsl:attribute>

     <xsl:attribute name='green-arrow'>
	<xsl:text>green &lt; &amp;</xsl:text>
     </xsl:attribute>

  </xsl:attribute-set>

</xsl:stylesheet>