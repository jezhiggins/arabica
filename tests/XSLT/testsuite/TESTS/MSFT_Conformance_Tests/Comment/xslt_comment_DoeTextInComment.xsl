<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- This stylesheet is a regression test case for bug 53329. It validates that
       a xsl:comment element cannot include a xsl:text element who has a disable
       -output-escaping attribute set to yes. -->

  <xsl:output method="xml" omit-xml-declaration="yes" indent="no"/>  

  <xsl:template match="/">
    <root>
     <xsl:comment>
	<xsl:text disable-output-escaping="yes">&lt;&gt;&amp;&apos;</xsl:text>
     </xsl:comment>
     <foo>bar</foo>
    </root>
  </xsl:template>

</xsl:stylesheet>