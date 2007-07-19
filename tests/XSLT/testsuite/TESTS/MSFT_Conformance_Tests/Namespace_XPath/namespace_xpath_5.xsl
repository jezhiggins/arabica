<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:p1="ns1">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <xsl:template match="proot:xslTutorial" xmlns:proot="ns_root">

    <!-- Redefine inherited prefix in the element -->
    <xsl:element name="{//p1:BBB/@id}" xmlns:p1="ns2"/>

    <!-- Use inherited prefix as originally declared -->
    <xsl:apply-templates select="p1:AAA[2]"/>

  </xsl:template>

  <xsl:template match="p1:AAA" xmlns:p2="ns3">
    <xsl:element name="{p2:CCC/@id}"/>
  </xsl:template>

  <xsl:template match="text()"/>
</xsl:stylesheet>