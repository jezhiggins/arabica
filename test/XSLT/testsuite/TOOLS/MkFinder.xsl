<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: MkFinder.xsl -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Given a test case catalog as input, produce a script (batch file, macro, whatever)
    that tests the existence of each file that should be shipped with the suite. This stylesheet also
    serves as a "sufficiency test" of the XSLT processor that you use to transform the catalog,
    since it uses all of the XSLT/XPath features needed for most purposes. -->

<xsl:output method="text" encoding="UTF-8" indent="no"/>

<!-- The following are the parts of a line in the script that will be the same each time. -->

<xsl:variable name="LineStart" select="'&#10; if not exist '"/>
<xsl:variable name="LinePart2" select="' echo '"/>
<xsl:variable name="LinePart3" select="' is missing '"/>

<!-- Here are named templates to create the opening lines and closing lines of the script.
    The lines in between will be generated on a one-line-per-file basis. -->

<xsl:template name="top">
  <!-- Below is the first line of the file. Every other generated line should have &#10; at the start
    to ensure that the result has a new-line where needed. -->
  <xsl:text>@echo off</xsl:text>
  <!-- We are producing a script that should be launched with the TESTS directory as the current
    directory. If you would like a script that runs from elsewhere, either add an appropriate CD (or
    equivalent) here, or prepend more directories on the file-path of each file-path generated in the
    main processing loop. -->
</xsl:template>

<xsl:template name="bottom">
  <!-- Below is the last line of the file. -->
  <xsl:text>&#10;echo DONE</xsl:text>
</xsl:template>

<!-- The templates below process file names and file-paths found in the catalog. -->

<xsl:template match="/">
  <xsl:call-template name="top"/>
  <xsl:apply-templates select="test-suite/test-catalog/test-case"/>
  <xsl:call-template name="bottom"/>
</xsl:template>

<xsl:template match="test-case">
  <!-- Construct path names relative to TESTS. -->
  <xsl:for-each select="scenario/input-file">
    <xsl:variable name="file" select="concat(../../../major-path,'/',../../file-path,'/',text())"/>
    <!-- Next line is for an MS-DOS batch file -->
    <xsl:variable name="fp" select="translate($file,'/','\')"/>
    <xsl:value-of select="concat($LineStart,$fp,$LinePart2,$fp,$LinePart3)"/>
  </xsl:for-each>
  <xsl:if test="scenario/@operation='standard' or scenario/@operation='result-analysis'">
    <xsl:for-each select="scenario/output-file">
      <xsl:variable name="file" select="concat(../../../major-path,'/REF_OUT/',../../file-path,'/',text())"/>
      <!-- Next line is for an MS-DOS batch file -->
      <xsl:variable name="fp" select="translate($file,'/','\')"/>
      <xsl:value-of select="concat($LineStart,$fp,$LinePart2,$fp,$LinePart3)"/>
    </xsl:for-each>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>