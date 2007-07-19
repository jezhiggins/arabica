<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	xmlns:a="i"
	xmlns:b="j"
	xmlns="k"
>
	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/">
		<xsl:apply-templates/>
	</xsl:template> 

   	<!-- Test various combinations of name and namespace AVT's -->
	<xsl:template match="root" xmlns:a="urn:foo"> 
		   <xsl:element name="{.//a:b}" xmlns="" namespace="abc">
			<xsl:element name="{.//a:b}" xmlns:a="urn:foo"/>
			<xsl:element name="b" />
			<xsl:element name="{.//a:b}" namespace="a"/>
			<xsl:element name="b:e" />
			<xsl:element name="b:e" xmlns:b="b" />
			<xsl:element name="b:e" xmlns:b="c" namespace="c"/>
			<xsl:comment>comment 1</xsl:comment>
			<xsl:element name="b:e" namespace="c" xmlns:b="bar">
			</xsl:element>
			<xsl:processing-instruction name="pi" blar="blar" xmlns:x="abc">pi 1</xsl:processing-instruction>
			<xsl:element name="{//@att}" namespace="x"/>
			<xsl:element name="{//@att1}" namespace="y"/>
			<xsl:element name="{//@att1}" namespace="y"/>
			<xsl:element name="{//@att1}" namespace="y"/>
			<!-- look for the element 'e:b' with namespae "urn:eee" and output the value as an element with namespace "abc" -->
			<xsl:element name="{.//e:b}" xmlns:e="urn:eee" namespace="abc"/>
		   </xsl:element>
    		<!--
    		<xsl:element name="a:b" namespace="x" />
		-->
	</xsl:template >

	<xsl:template match="text()" />

</xsl:stylesheet>
