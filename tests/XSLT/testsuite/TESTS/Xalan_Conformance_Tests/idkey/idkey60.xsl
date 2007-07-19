<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: idkey60 -->
  <!-- Document: http://www.w3.org/TR/xslt -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 5.2 -->
  <!-- Purpose: Try multiple child steps after id() in match patterns -->
  <!-- Creator: Henry Zongaro -->

<xsl:output method="xml" encoding="UTF-8" indent="no"/>

  <xsl:template match='/'>
    <out>
      <xsl:apply-templates/><!-- rely on some built-ins -->
    </out>
  </xsl:template>

  <xsl:template match='id("abc")/l1/v'>
    <xsl:text>
</xsl:text>
    <match-l1-v>
      <xsl:value-of select='.'/>
    </match-l1-v>
  </xsl:template>

  <xsl:template match='id("abc")/l2/v'>
    <xsl:text>
</xsl:text>
    <match-l2-v>
      <xsl:value-of select='.'/>
    </match-l2-v>
  </xsl:template>

  <xsl:template match='id("abc")/l1/l2/w'>
    <xsl:text>
</xsl:text>
    <match-l1-l2-w>
      <xsl:value-of select='.'/>
    </match-l1-l2-w>
  </xsl:template>

  <xsl:template match='id("abc")/l3/v'>
    <xsl:text>
</xsl:text>
    <match-l3-v>
      <xsl:value-of select='.'/>
    </match-l3-v>
  </xsl:template>

  <xsl:template match='v'>
    <xsl:text>
</xsl:text>
    <match-v>
      <xsl:value-of select='.'/>
    </match-v>
  </xsl:template>

  <xsl:template match='text()'/><!-- squelch direct replay of text -->

</xsl:stylesheet>
