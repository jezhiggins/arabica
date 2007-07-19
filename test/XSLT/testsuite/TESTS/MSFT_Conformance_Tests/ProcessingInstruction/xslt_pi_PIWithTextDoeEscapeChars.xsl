<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:output method="xml" omit-xml-declaration="yes" indent="no"/>  

  <xsl:template match="/">
    <root>

     <xsl:processing-instruction name="doe">
	<xsl:text disable-output-escaping="yes">&lt;&quot;&gt;&amp;&apos;</xsl:text>
     </xsl:processing-instruction>

     <foo>bar</foo>

     <xsl:processing-instruction name="doe">
	<xsl:value-of disable-output-escaping="yes" select='/root/text' />
     </xsl:processing-instruction>

     <foo>bar2</foo>

    </root>
  </xsl:template>

</xsl:stylesheet>