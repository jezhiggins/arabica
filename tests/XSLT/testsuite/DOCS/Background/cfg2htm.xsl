<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<!--
Copyright (C) The Organization for the Advancement of
Structured Information Standards [OASIS] (2001). All Rights
Reserved.

This document and translations of it may be copied and
furnished to others, and derivative works that comment on
or otherwise explain it or assist in its implementation may
be prepared, copied, published and distributed, in whole
or in part, without restriction of any kind, provided that the
above copyright notice and this paragraph are included on
all such copies and derivative works. However, this
document itself may not be modified in any way, such as by
removing the copyright notice or references to OASIS,
except as needed for the purpose of developing OASIS
specifications, in which case the procedures for copyrights
defined in the OASIS Intellectual Property Rights document
must be followed, or as required to translate it into
languages other than English.

The limited permissions granted above are perpetual and
will not be revoked by OASIS or its successors or assigns.

This document and the information contained herein is
provided on an "AS IS" basis and OASIS DISCLAIMS ALL
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO ANY WARRANTY THAT THE USE
OF THE INFORMATION HEREIN WILL NOT INFRINGE
ANY RIGHTS OR ANY IMPLIED WARRANTIES OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR
PURPOSE.
-->
<xsl:output doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

<xsl:template match="/">
  <html>
    <head>
      <title>
        <xsl:text>Test regime for </xsl:text>
        <xsl:value-of select="/suite/info/committee"/>
      </title>
    </head>
    <body>
      <h1>
        <xsl:text>Test regime for </xsl:text>
        <xsl:value-of select="/suite/info/committee"/>
      </h1>
      <h2>1. Introduction</h2>
      <xsl:copy-of select="/suite/info/desc/node()"/>
      <h2>2. Status values allowed for discretionary items</h2>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="2"/>
        <xsl:with-param name="heading" select="'h3'"/>
        <xsl:with-param name="section" select="/suite/discretion-statuses"/>
        <xsl:with-param name="element" select="'item'"/>
        <xsl:with-param name="attribute" select="'status'"/>
      </xsl:call-template>
      <h2>3. Test case categories</h2>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="3"/>
        <xsl:with-param name="heading" select="'h3'"/>
        <xsl:with-param name="section" select="/suite/categories"/>
        <xsl:with-param name="element" select="'test-case'"/>
        <xsl:with-param name="attribute" select="'category'"/>
      </xsl:call-template>
      <h2>4. Citations into Recommendation documents</h2>
      <xsl:copy-of select="/suite/citations/desc/node()"/>
      <h3>4.1 Citation types</h3>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="4.1"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/citations/citation-types"/>
        <xsl:with-param name="element" select="'spec-citation'"/>
        <xsl:with-param name="attribute" select="'type'"/>
      </xsl:call-template>
      <h3>4.2 Citation specifications</h3>
      <xsl:call-template name="document-citations">
        <xsl:with-param name="index" select="4.2"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/citations/citation-specifications"/>
      </xsl:call-template>
      <h2>5. Gray areas</h2>
      <xsl:copy-of select="/suite/gray-areas/desc/node()"/>
      <xsl:call-template name="document-gray">
        <xsl:with-param name="index" select="5"/>
        <xsl:with-param name="heading" select="'h3'"/>
        <xsl:with-param name="section" 
                        select="/suite/gray-areas"/>
      </xsl:call-template>
      <h2>6. Scenarios</h2>
      <xsl:copy-of select="/suite/scenarios/desc/node()"/>
      <h3>6.1 Operations</h3>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="6.1"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/scenarios/operations"/>
        <xsl:with-param name="element" select="'scenario'"/>
        <xsl:with-param name="attribute" select="'operation'"/>
      </xsl:call-template>
      <h3>6.2 Roles for input and output files</h3>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="6.2"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/scenarios/roles"/>
        <xsl:with-param name="element" select="'input-file/output-file'"/>
        <xsl:with-param name="attribute" select="'role'"/>
      </xsl:call-template>
      <h3>6.3 Comparison types for output files</h3>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="6.3"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/scenarios/comparisons"/>
        <xsl:with-param name="element" select="'output-file'"/>
        <xsl:with-param name="attribute" select="'compare'"/>
      </xsl:call-template>
      <h3>6.4 Parameter types during invocation</h3>
      <xsl:call-template name="document-section">
        <xsl:with-param name="index" select="6.4"/>
        <xsl:with-param name="heading" select="'h4'"/>
        <xsl:with-param name="section" 
                        select="/suite/scenarios/parameter-types"/>
        <xsl:with-param name="element" select="'param-set'"/>
        <xsl:with-param name="attribute" select="'type'"/>
      </xsl:call-template>
      <small><strong><xsl:value-of select="suite/@date"/></strong></small>
    </body>
  </html>
</xsl:template>

<xsl:template name="document-section">
  <xsl:param name="index"/>
  <xsl:param name="heading"/>
  <xsl:param name="section"/>
  <xsl:param name="element"/>
  <xsl:param name="attribute"/>

  <xsl:copy-of select="$section/desc/node()"/>
  <xsl:for-each select="$section/*[@id]">
    <xsl:element name="{$heading}">
      <xsl:value-of select="$index"/>.<xsl:value-of select="position()"/>
      <xsl:text> </xsl:text>
      <samp>
        <xsl:text>&lt;</xsl:text>
        <xsl:value-of select="$element"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="$attribute"/>
        <xsl:text>="</xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>"></xsl:text>
      </samp>
    </xsl:element>
    <xsl:copy-of select="node()"/>
  </xsl:for-each>
</xsl:template>

<xsl:template name="document-citations">
  <xsl:param name="index"/>
  <xsl:param name="heading"/>
  <xsl:param name="section"/>

  <xsl:copy-of select="$section/desc/node()"/>
  <xsl:for-each select="$section/cite-spec">
    <xsl:for-each select="version-spec">
      <xsl:for-each select="spec">
        <xsl:element name="{$heading}">
          <xsl:value-of select="$index"/>.<xsl:text/>
          <xsl:number count="spec" level="any"
            from="citation-specifications"/>
          <xsl:text> </xsl:text>
          <samp>
            <xsl:text>&lt;spec-citation spec="</xsl:text>
            <xsl:value-of select="../../@id"/>
            <xsl:text>" version="</xsl:text>
            <xsl:value-of select="../@version"/>
            <xsl:text>" type="</xsl:text>
            <xsl:value-of select="@type"/>
            <xsl:text>"></xsl:text>
          </samp>
        </xsl:element>
        <xsl:copy-of select="../../desc/node()"/>
        <xsl:copy-of select="../desc/node()"/>
        <xsl:copy-of select="node()"/>
      </xsl:for-each>
    </xsl:for-each>
  </xsl:for-each>
</xsl:template>

<xsl:template name="document-gray">
  <xsl:param name="index"/>
  <xsl:param name="heading"/>
  <xsl:param name="section"/>
  <xsl:for-each select="$section/gray-area">
    <xsl:element name="{$heading}">
      <xsl:value-of select="$index"/>.<xsl:text/>
      <xsl:value-of select="position()"/>
      <xsl:text> </xsl:text>
      <samp>
        <xsl:text>&lt;gray-area-choice name="</xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>"></xsl:text>
      </samp>
    </xsl:element>
    <ul>
      <xsl:for-each select="choices/choice">
        <li><samp>behavior="<xsl:value-of select="@value"/>"</samp></li>
      </xsl:for-each>
    </ul>
    <xsl:copy-of select="desc/node()"/>
    <xsl:for-each select="spec-citation">
      <xsl:variable name="spec" select="@spec"/>
      <xsl:variable name="version" select="@version"/>
      <xsl:variable name="type" select="@type"/>
      <xsl:variable name="place" select="@place"/>
      <xsl:if test="id(string($type))/@method='human'">
        <xsl:for-each select="id(string($spec))/
                              version-spec[@version=$version]/
                              spec[@type=$type]">
          <li>
            <xsl:value-of select="@prefix"/>
            <xsl:choose>
              <xsl:when test="@ref-linkable='yes'">
                <a href="{@ref}"><xsl:value-of select="@ref"/></a>
              </xsl:when>
              <xsl:otherwise>
                <xsl:value-of select="@ref"/>
              </xsl:otherwise>
            </xsl:choose>
            <xsl:value-of select="concat(@infix,$place,@suffix)"/>
          </li>
        </xsl:for-each>
      </xsl:if>
      <xsl:if test="id(string($type))/@method='machine'">
        <xsl:for-each select="id(string($spec))/
                              version-spec[@version=$version]/
                              spec[@type=$type]">
          <xsl:variable name="ref"
                        select="concat(@prefix,@ref,@infix,$place,@suffix)"/>
          <li>
            <a href="{$ref}"><xsl:value-of select="$ref"/></a>
          </li>
        </xsl:for-each>
      </xsl:if>
    </xsl:for-each>
  </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
