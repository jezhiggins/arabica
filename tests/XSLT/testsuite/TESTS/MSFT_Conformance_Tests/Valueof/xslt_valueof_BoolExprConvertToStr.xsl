<?xml version='1.0'?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- This stylesheet is a test case for regression of bug #60548. It validates that
	the boolean evaluated value in the select cases is convert to a string. -->

	<xsl:output omit-xml-declaration="yes" />
    
	<xsl:template match="/">
		<root>	
		    <header>boolean(0) = <xsl:value-of select="boolean(0)"/></header>
		    <header>boolean(1) = <xsl:value-of select="boolean(1)"/></header>
		    <footer>string(boolean(0)) = <xsl:value-of select="string(boolean(0))"/></footer>
		    <footer>string(boolean(1)) = <xsl:value-of select="string(boolean(1))"/></footer>
		</root>
	</xsl:template>

</xsl:stylesheet>