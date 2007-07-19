<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	xmlns="k"
>
	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
		<xsl:apply-templates/>
	</xsl:template>

   	<!-- Test various combinations of name and namespace AVT's -->
	<xsl:template match="root" > 
		   <xsl:element name="a" namespace="" >
			<xsl:attribute name="a"  namespace="{.//a}"/>
			<xsl:attribute name="{.//a}"  namespace="a"/>
			<xsl:attribute name='xmlns:c1'>xmlns::{bbbcccd}</xsl:attribute>
			<xsl:attribute name='xml:{.//b}' namespace="{.//b}" >{.//b}</xsl:attribute>
			<xsl:element name="{.//a}"  namespace="{.//a}">
				<xsl:attribute name='{.//@c1}:{.//@c2}' namespace="{.//a}::{{{.//b}{c}}}">{.//c}</xsl:attribute>
			</xsl:element>
		   </xsl:element>
	</xsl:template >

	<xsl:template match="text()" />

</xsl:stylesheet>
