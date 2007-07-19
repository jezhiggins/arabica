<!-- Test file for Bug # 70879 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output encoding="UTF-8" indent="yes"/>

    <xsl:attribute-set name="empty"/>

    <xsl:attribute-set name="set" use-attribute-sets="empty">
		<xsl:attribute name="foo"/>
    </xsl:attribute-set>

</xsl:stylesheet>