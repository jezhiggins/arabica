<?xml version="1.0" encoding="utf-8"?>
<!--Script to validate catalogues against test suite configuration-->
<!--$Date: 2001/11/17 22:31:12 $(UTC)-->

<!--not documented yet-->
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

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:variable name="configuration" 
              select="document(/submissions/@configuration-href,
                               /submissions/@configuration-href)"/>
<xsl:variable name="discretionary"
              select="document(/submissions/@discretionary-href,
                               /submissions/@discretionary-href)"/>

<xsl:output indent="yes"/>

<xsl:template match="/">
  <problems>
    <xsl:if test="not($configuration)">
      <xsl:variable name="err">
        <xsl:text>Configuration file '</xsl:text>
        <xsl:value-of select="/submissions/@configuration-href"/>
        <xsl:text>' not found.</xsl:text>
      </xsl:variable>
      <problem><xsl:copy-of select="$err"/></problem>
      <xsl:message terminate="yes"><xsl:copy-of select="$err"/></xsl:message>
    </xsl:if>
    <xsl:if test="not($discretionary)">
      <xsl:variable name="err">
        <xsl:text>Discretionary file '</xsl:text>
        <xsl:value-of select="/submissions/@discretionary-href"/>
        <xsl:text>' not found.</xsl:text>
      </xsl:variable>
      <problem><xsl:copy-of select="$err"/></problem>
      <xsl:message terminate="yes"><xsl:copy-of select="$err"/></xsl:message>
    </xsl:if>
    <xsl:variable name="discretionary-configuration-href"
                  select="$discretionary/doc/@configuration-href"/>
    <xsl:if test="$discretionary">
      <xsl:if test="generate-id(document($discretionary-configuration-href,
                                         $discretionary-configuration-href))
                  !=generate-id($configuration)">
        <problem>Configuration file supplied (<xsl:text/>
          <xsl:value-of select="/submissions/@configuration-href"/>
          <xsl:text>) is not pointing to same file as the </xsl:text>
          <xsl:text>discretionary document's configuration file (</xsl:text>
          <xsl:value-of select="$discretionary-configuration-href"/>
          <xsl:text>)</xsl:text>
        </problem>
      </xsl:if>
    </xsl:if>
    <xsl:for-each select="/submissions/submission">
      <xsl:apply-templates select="document(@href,@href)/
                                   test-suite/test-catalog">
        <xsl:with-param name="submitter" select="@submitter"/>
        <xsl:with-param name="sub-date" select="@date"/>
      </xsl:apply-templates>
    </xsl:for-each>
  </problems>
</xsl:template>

<xsl:template match="test-catalog">
  <xsl:param name="submitter"/> <!--used for uniqueness of each submission;
                                    assumed to not include "_" character-->
  <xsl:param name="sub-date"/>
  <catalog submitter="{$submitter}" date="{$sub-date}">
    <xsl:for-each select="test-case">
      <xsl:variable name="id" select="normalize-space(@id)"/>
      <xsl:call-template name="validate-date">
        <xsl:with-param name="node" select="date"/>
        <xsl:with-param name="id" select="$id"/>
      </xsl:call-template>

      <!--those singleton items validated against the suite configuration-->
      <xsl:variable name="category" select="@category"/>
      <xsl:variable name="operation" select="scenario/@operation"/>

      <xsl:for-each select="$configuration">
        <xsl:if test="name(id(string($category))) != 'category'">
          <problem prob-id="{$id}" value="{$category}"
                                        >bad test case category value</problem>
        </xsl:if>
        <xsl:if test="name(id(string($operation))) != 'operation'">
          <problem prob-id="{$id}" value="{$operation}"
                                        >bad scenario operation value</problem>
        </xsl:if>
      </xsl:for-each>

      <!--those multiple items validated against the suite configuration-->
      <xsl:for-each select="spec-citation">
        <xsl:variable name="spec" select="@spec"/>
        <xsl:variable name="type" select="@type"/>
        <xsl:variable name="place" select="@place"/>
        <xsl:for-each select="$configuration">
          <xsl:if test="name(id(string($spec))) != 'cite-spec'">
            <problem prob-id="{$id}" value="{$spec}"
                                             >bad citation spec value</problem>
          </xsl:if>
          <xsl:if test="name(id(string($type))) != 'cite-type'">
            <problem prob-id="{$id}" value="{$type}"
                                             >bad citation type value</problem>
          </xsl:if>
          <xsl:if test="not(normalize-space($place))">
            <problem prob-id="{$id}">missing citation place</problem>
          </xsl:if>
        </xsl:for-each>
        <xsl:call-template name="validate-date">
          <xsl:with-param name="node" select="@errata-add-date"/>
        </xsl:call-template>
        <xsl:call-template name="validate-date">
          <xsl:with-param name="node" select="@errata-drop-date"/>
        </xsl:call-template>
      </xsl:for-each>
      <xsl:for-each select="scenario/output-file">
        <xsl:variable name="compare" select="@compare"/>
        <xsl:for-each select="$configuration">
          <xsl:if test="name(id(string($compare))) != 'comparison'">
            <problem prob-id="{$id}" value="{$compare}"
                                         >bad output comparison value</problem>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>
      <xsl:for-each select="scenario/output-file/@role | 
                            scenario/input-file/@role">
        <xsl:variable name="role" select="."/>
        <xsl:for-each select="$configuration">
          <xsl:if test="name(id(string($role))) != 'role'">
            <problem prob-id="{$id}" value="{$role}"
                                      >bad file role comparison value</problem>
          </xsl:if>
          <xsl:if test="not(string($role/..))">
            <problem prob-id="{$id}" value="{$role}"
                                       >empty file name specification</problem>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>
      <xsl:variable name="files"
                    select="scenario/output-file | scenario/input-file"/>
      <xsl:for-each select="$configuration/suite/scenarios/roles/
                            role[@required]">
        <xsl:if test="not($files[local-name()=current()/@required]
                                [@role=current()/@id])">
          <problem prob-id="{$id}" value="{@id}"
                                          >required role not included</problem>
        </xsl:if>
      </xsl:for-each>
      <xsl:for-each select="scenario/param-set/@type">
        <xsl:variable name="type" select="."/>
        <xsl:for-each select="$configuration">
          <xsl:if test="name(id(string($type))) != 'parameter-type'">
            <problem prob-id="{$id}" value="{$type}"
                                                  >bad parameter type</problem>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>

      <!--those items that are validated against the discretionary items-->
      <xsl:for-each select="discretionary/discretionary-choice">
        <xsl:variable name="name" select="@name"/>
        <xsl:variable name="behavior" select="@behavior"/>
        <xsl:for-each select="$discretionary">
          <xsl:choose>
            <xsl:when test="name(id(string($name))) != 'item'">
              <problem prob-id="{$id}" value="{$name}"
                                      >bad discretionary choice value</problem>
            </xsl:when>
            <xsl:otherwise>
              <xsl:if test="not(id(string($name))/choices/
                                choice[@value=$behavior])">
                <problem prob-id="{$id}" value="{$behavior}"
                        >bad behaviour for given discretionary choice</problem>
              </xsl:if>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </xsl:for-each>

      <!--those items that are validated against gray areas-->
      <xsl:for-each select="gray-area/gray-area-choice">
        <xsl:variable name="name" select="@name"/>
        <xsl:variable name="behavior" select="@behavior"/>
        <xsl:for-each select="$configuration">
          <xsl:choose>
            <xsl:when test="name(id(string($name))) != 'gray-area'">
              <problem prob-id="{$id}" value="{$name}"
                                          >bad gray-area choice value</problem>
            </xsl:when>
            <xsl:otherwise>
              <xsl:if test="not(id(string($name))/choices/
                                choice[@value=$behavior])">
                <problem prob-id="{$id}" value="{$behavior}"
                            >bad behaviour for given gray-area choice</problem>
              </xsl:if>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </xsl:for-each>
    </xsl:for-each>
  </catalog>
</xsl:template>

<xsl:template name="validate-date">
  <xsl:param name="node"/>
  <xsl:param name="id"/>
  <xsl:variable name="date" select="normalize-space(node)"/>

  <xsl:if test="node and ( string-length(translate($date,'/-',''))!=8 or 
                           translate($date,'0123456789/-','') )">
    <problem prob-id="{$id}" value="{$date}">bad date format</problem>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>
