<!-- This test validates that an error condition is raised. In the example below, the source file for
this transform (xslt_element_NSShared.xml) utilizes the namespace ns1 as 'a'. It is picked up by
the stylesheet in xsl:element, but the namespace is unrecognized by this stylesheet. -->


<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			      xmlns:p1="ns1">

  <xsl:output omit-xml-declaration="yes" />

  <xsl:template match="/">
    <root>
	<xsl:apply-templates/>
    </root>
  </xsl:template>

  <!-- Check that xml prefix is predefined in the xml document -->
  <!-- p1 is namespace 'a' in the source document -->
  <xsl:template match="p1:AAA">
    <xsl:element name="{name(.)}" >
    </xsl:element>
  </xsl:template>

</xsl:stylesheet>