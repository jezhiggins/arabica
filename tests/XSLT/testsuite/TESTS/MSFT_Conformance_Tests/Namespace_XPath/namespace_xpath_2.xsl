<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- Undeclared prefix should throw exception in xpath -->
  <xsl:template match="a:AAA">
    <xsl:copy>
	<xsl:value-of select="@id"/>
	<xsl:apply-templates/>
    </xsl:copy>
  </xsl:template>


</xsl:stylesheet>