<!-- UTF-8 -->
<!-- Single-template cases -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <!-- Regression for bug #89780 - Use relative select query in a single-template stylesheet -->
    <xsl:value-of select="bookstore/book[1]/author/last-name"/>

    <!-- Use variables in single template stylesheet -->
    <xsl:variable name="foo" select="'hello'"/>
    <xsl:if test="$foo">
        <xsl:value-of select="$foo"/>
    </xsl:if>
</html>
