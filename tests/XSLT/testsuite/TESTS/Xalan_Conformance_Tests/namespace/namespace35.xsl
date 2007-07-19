<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:axsl="http://www.w3.org/1999/XSL/TransformAlias"
  version="1.0">

<xsl:namespace-alias result-prefix="xsl" stylesheet-prefix="axsl" />
<xsl:output method="xml" indent="yes"/>

  <!-- FileName: namespace35 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Get xmlns declaration attached to outermost LRE.
     Prefix "axsl" should also be literal. -->

<xsl:template match="/">
  <axsl:template match="/"/>
</xsl:template>

</xsl:stylesheet>
