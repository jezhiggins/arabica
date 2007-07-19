<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position111 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5 -->
  <!-- Creator: David Bertoni, amended by David Marston -->
  <!-- Purpose: Data Model requires that namespace nodes precede attribute nodes. -->

<xsl:output encoding="UTF-8" method="xml" indent="no"/>

<xsl:template match="Doc">
  <out>
    <xsl:for-each select="namespace::* | attribute::*" >
      <xsl:choose>
        <xsl:when test="contains(.,'http')">
          <!-- it's a namespace node -->
          <xsl:if test="position() &lt;= 3">
            <xsl:text> OK</xsl:text>
          </xsl:if>
        </xsl:when>
        <xsl:when test="contains(.,'attr')">
          <!-- it's an attribute node -->
          <xsl:if test="position() &gt; 3">
            <xsl:text> OK</xsl:text>
          </xsl:if>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>&#10;BAD VALUE: </xsl:text><xsl:value-of select="."/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
  </out>
</xsl:template>

</xsl:stylesheet>