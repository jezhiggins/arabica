<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:variable name="meth" select="xml"/>
<xsl:variable name="dec" select="yes"/>
<xsl:variable name="ind" select="yes"/> 

<xsl:output method="xml" encoding="unicode" omit-xml-declaration="yes"/>  
<xsl:template match="/"> 

	<xsl:element name="x:a" xmlns:x="uri1" xmlns:y="uri1">
  <xsl:element name="y:a">boo</xsl:element>
</xsl:element>

 
<xsl:copy-of select="/xslTutorial"/>  
Expected results: 
&lt;x:a xmlns:x="uri1"&gt;
  &lt;y:a xmlns:y="uri1"&gt;boo&lt;/y:a&gt;
&lt;/x:a&gt;

</xsl:template> 

</xsl:stylesheet>  
