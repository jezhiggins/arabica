<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:a="ns1"
			      xmlns:foo="ns2"
			      xmlns:bar="ns3">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- This prefix declared the same in xml file -->
  <xsl:template match="a:AAA">
    <xsl:copy>
	<xsl:value-of select="@id"/>
	<xsl:apply-templates/>
    </xsl:copy>
  </xsl:template>

  <!-- This prefix declared differently in xml file -->
  <xsl:template match="foo:BBB">
    <xsl:copy>
	<xsl:value-of select="@id"/>
	<xsl:apply-templates/>
    </xsl:copy>
  </xsl:template>

  <!-- This prefix declared differently in xml file -->
  <xsl:template match="bar:*">
    <xsl:copy>
	<xsl:value-of select="@id"/>
	<xsl:apply-templates/>
    </xsl:copy>
  </xsl:template>

  <!-- Avoid extraneous whitespace -->
  <xsl:template match="text()"/>

</xsl:stylesheet>