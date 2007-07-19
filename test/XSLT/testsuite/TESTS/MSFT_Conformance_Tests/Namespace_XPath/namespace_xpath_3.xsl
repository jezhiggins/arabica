<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:p1="ns1"
			      xmlns:p2="ns2"
			      xmlns:p3="ns_root">

  <!-- Use matches method on XmlNavigator -->
  <xsl:template match="p3:xslTutorial">
    <root>

    <!-- Use select method on XmlNavigator -->
    <xsl:for-each select="p1:AAA">

	<!-- Use evaluate method on XmlNavigator -->
	<xsl:element name="{p2:BBB/@id}"/>

    </xsl:for-each>

    </root>
  </xsl:template>

  <xsl:template match="text()"/>

</xsl:stylesheet>