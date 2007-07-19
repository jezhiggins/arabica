<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

      <!-- try to outpu a valid xml file with schema -->
      <xsl:template match="/">
	<xsl:element name="root">

	 <xsl:element name="Schema">

	  <xsl:attribute name="name">Schema1</xsl:attribute>
	  <xsl:attribute name="xmlns">urn:schemas-microsoft-com:xml-data</xsl:attribute>

	  <xsl:element name="ElementType">
	   <xsl:attribute name="name">e1</xsl:attribute>
	   <xsl:attribute name="dt:type" namespace="urn:schemas-micrsooft-com:datatypes">int</xsl:attribute>
	  </xsl:element >

	  <xsl:element name="ElementType">
	   <xsl:attribute name="name">e</xsl:attribute>
	   <xsl:attribute name="content">eltOnly</xsl:attribute>
	   <xsl:element name="element">
	    <xsl:attribute name="type">e1</xsl:attribute>
	   </xsl:element >
	  </xsl:element >

	 </xsl:element >

	 <xsl:element name="Schema">

	  <xsl:attribute name="name">Schema2</xsl:attribute>
	  <xsl:attribute name="xmlns">urn:schemas-microsoft-com:xml-data</xsl:attribute>

	  <xsl:element name="ElementType">
	   <xsl:attribute name="name">e1</xsl:attribute>
	   <xsl:attribute name="dt:type" namespace="urn:schemas-micrsooft-com:datatypes">int</xsl:attribute>
	  </xsl:element >

	  <xsl:element name="ElementType">
	   <xsl:attribute name="name">e</xsl:attribute>
	   <xsl:attribute name="content">eltOnly</xsl:attribute>
	   <xsl:element name="element">
	    <xsl:attribute name="type">e1</xsl:attribute>
	   </xsl:element >
	  </xsl:element >

	 </xsl:element >
	 
	 <xsl:element name="x:e" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	   <xsl:attribute name="foo" namespace="foo">bar</xsl:attribute>
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="urn:bar">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="urn:foo">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  <xsl:element name="x:e1" namespace="x-schema:#Schema1">
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	  </xsl:element>
	 </xsl:element>
	</xsl:element >

      </xsl:template>

      <xsl:template match="text()" />
</xsl:stylesheet>
