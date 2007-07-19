<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Test for DCR 53329. Validates that use of a result tree fragment does not affect
       (though not implemented) a stylesheet negatively.
  -->

  <xsl:output method="xml" omit-xml-declaration="no" indent="no" encoding='utf-8' />  

  <xsl:variable name='foo'>
	<foo>
	   <xsl:text disable-output-escaping='yes'>
	      &lt; &amp; dog &gt; &apos; &quot;
	   </xsl:text>
	</foo>
  </xsl:variable>

  <xsl:template match="/">
    <bareroot>
	<xsl:value-of select='$foo' />
	<xsl:copy-of select='$foo' />
    </bareroot>
  </xsl:template>

</xsl:stylesheet>