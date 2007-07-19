<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	xmlns="k"
>
	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<!-- combination of child nodes under xsl:element  -->

	<xsl:template match="/">
	<root>
		<xsl:element name="a:b" xmlns="aaa" namespace="a:b">
		   <!-- xsl:text inside an xsl:element -->
		   <xsl:text disable-output-escaping="no">
			x &lt; &gt; &amp; &apos; &quot; 
		   </xsl:text>

		   	<!-- some literal text inside an xsl:element -->
			x &lt; &gt; &amp; &apos; &quot; 
			&#x20;  &#x59; &#x60; &#x61; &#x62;
			&#xA; &#xD;
			y

		   <!-- another xsl:text inside an xsl:element -->
		   <xsl:text>
			text
		   </xsl:text>

		   <xsl:comment> 
			&amp;abc; &lt;  > 
			<![CDATA[ cdata node should not be ignored ]]>
			<!-- these should be ignored -->
			<xsl:element name="INSIDE" />  
			<abc>xxxxxx</abc>
		   </xsl:comment>

		   <xsl:processing-instruction name="PI-NODE"> 
			&amp;abc; &lt;  > 
			<![CDATA[ cdata node should not be ignored ]]>
			<!-- these should be ignored -->
			<xsl:element name="INSIDE" />  
			<abc>xxxxxx</abc>
		   </xsl:processing-instruction>

		   <xsl:comment> &amp;abc; &lt;  > </xsl:comment>

		</xsl:element>
		<xsl:element name="b" namespace="a" xmlns="b">
			&amp;abc; &lt;  > 
			<![CDATA[ cdata node should not be ignored ]]>
			<!-- these should be ignored -->
			<xsl:element name="INSIDE" />  

			<abc>xxxxxx</abc>
			<!-- ccccccccc -->
			<?pi pppppppppppp?>
			<![CDATA[ cdcdcdcdcdcdcd ]]>
		</xsl:element>
	</root>
	</xsl:template> 

	<xsl:template match="text()" />


</xsl:stylesheet>
