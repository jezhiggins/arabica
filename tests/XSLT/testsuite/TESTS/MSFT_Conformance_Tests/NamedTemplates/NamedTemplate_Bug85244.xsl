<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="xml" omit-xml-declaration="yes"/>

      <xsl:template match="a | b" name="foo">
	Inside named template
      </xsl:template>

      <xsl:template match="/">
		<out><xsl:call-template name="foo"/></out>
      </xsl:template>

</xsl:stylesheet>