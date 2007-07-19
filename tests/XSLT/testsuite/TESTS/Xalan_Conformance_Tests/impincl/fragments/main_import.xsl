<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- FileName: main_import (version for directory one level down) -->
<!-- Purpose: Used by impincl19 -->
<!--   This is the third file in the import chain. It's imported by the one in the frag-subdir. -->

<xsl:import href="../main_import.xsl"/>

<xsl:template match="test">
In Fragments: <xsl:value-of select="."/>
<xsl:apply-imports/>
</xsl:template>

</xsl:stylesheet>