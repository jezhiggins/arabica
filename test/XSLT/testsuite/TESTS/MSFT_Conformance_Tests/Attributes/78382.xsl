<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

	<root>
		<xsl:attribute name="a" namespace="a">aaa</xsl:attribute >
		<xsl:attribute name="a" namespace="a">xxx</xsl:attribute >

		<xsl:attribute name="x:a" namespace="a">bbb</xsl:attribute >
		<xsl:attribute name="x:a" namespace="a">abc</xsl:attribute >

		<xsl:attribute name="a" namespace="a">xxx</xsl:attribute >
		<xsl:attribute name="x:a" namespace="a">bbb</xsl:attribute >

		<xsl:attribute name="a" namespace="b">iii</xsl:attribute >
		<xsl:attribute name="x:a" namespace="b">jjj</xsl:attribute >

		<xsl:attribute name="a" namespace="b">kkk</xsl:attribute >
		<xsl:attribute name="y:a" namespace="b">jjj</xsl:attribute >

	</root>
</html>
