<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- FileName: main_import (version for same directory as impincl19) -->
<!-- Purpose: Used by impincl19 -->
<!--   This is the last file in the import chain. Main XSLT file is in same directory. -->

<xsl:template match="test">
In ImpIncl: <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>