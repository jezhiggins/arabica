<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <!-- This stylesheet is a test case regression of bug 65760. It validates that
         an exception is thrown when the xsl include element is placed before the
	 the xsl import element. -->

    <xsl:output method="xml" omit-xml-declaration="yes" />
    <xsl:include href="xslt_import_IncludeBeforeImport1.xsl"/>
    <xsl:import href="xslt_import_IncludeBeforeImport2.xsl"/>

</xsl:stylesheet>
