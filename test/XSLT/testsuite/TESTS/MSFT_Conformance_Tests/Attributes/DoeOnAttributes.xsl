<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Test for DCR 53329. -->

  <xsl:output method="xml" omit-xml-declaration="yes" indent="no"/>  

  <xsl:template match="/">
    <root>

	<xsl:element name="XslElement">
	   <xsl:attribute name="Foo">
	      <xsl:text disable-output-escaping='yes'> &gt; &lt; &apos; &quot; &amp; &#x51; &#x3C; &#x26; </xsl:text>
	   </xsl:attribute>
	</xsl:element>

	<LitResult>
	   <xsl:attribute name="Bar">
	      <xsl:text disable-output-escaping='yes'> &gt; &lt; &apos; &quot; &amp; &#x51; &#x3C; &#x26; </xsl:text>
	   </xsl:attribute>
	</LitResult>


	<xsl:element name="XslElement">
	   <xsl:attribute name="Foo">
	      <xsl:value-of disable-output-escaping='yes' select='/root/text' />
	   </xsl:attribute>
	</xsl:element>

	<LitResult>
	   <xsl:attribute name="Bar">
	      <xsl:value-of disable-output-escaping='yes' select='/root/text' />
	   </xsl:attribute>
	</LitResult>	

    </root>
  </xsl:template>

</xsl:stylesheet>