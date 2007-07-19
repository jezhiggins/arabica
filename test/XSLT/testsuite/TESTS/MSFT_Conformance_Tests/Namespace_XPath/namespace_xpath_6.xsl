<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:p0="ns0"
			      xmlns:p1="ns1"
			      xmlns:namespace="http://www.w3.org/XML/1998/namespace"
			      xmlns:a="ns_output">

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- Check that xml prefix is predefined in the xml document -->
  <xsl:template match="p1:AAA">
    <xsl:element name="{name(.)}">
	<xsl:attribute name="{name(@namespace:space)}">
	    <xsl:value-of select="@namespace:space"/>
	</xsl:attribute>
	<xsl:value-of select="@id"/>
    </xsl:element>
    <xsl:apply-templates select=".//p0:DDD"/>
  </xsl:template>

  <!-- Check that xml prefix is predefined in the stylesheet -->
  <xsl:template match="p0:DDD">
    <xsl:element name="{name(.)}">
	<xsl:attribute name="xml:space">
	    <xsl:value-of select="@xml:space"/>
	</xsl:attribute>
	<xsl:value-of select="@id"/>
    </xsl:element>
  </xsl:template>

  <xsl:template match="text()"/>
</xsl:stylesheet>