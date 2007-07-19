<?xml version="1.0"?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: ImpIncl17 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.6.2 -->
  <!-- Purpose: Test of importing a stylesheet involving keys. -->
  <!-- Author: Claudio Sacerdoti Coen, revised by David Marston -->

<!-- Uncomment either line below if keyspace fails when defined only in import. -->
<!-- <xsl:key name="id" use="@id" match="LAMBDA"/> -->
<!-- <xsl:key name="annid" use="@of" match="Annotation"/> -->

<xsl:import href="fragments/imp17all.xsl"/>

</xsl:stylesheet>
