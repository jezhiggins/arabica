<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Different match patterns in template for functional code coveage -->

<xsl:template match="//bar[1] | foo/bar[2]">
  <out><xsl:value-of select="@attr" /></out>
</xsl:template>
</xsl:stylesheet>