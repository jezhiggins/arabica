<!-- UTF-8 -->
<!DOCTYPE html [
<!ELEMENT html EMPTY>
<!ATTLIST html
            attr CDATA #IMPLIED
            xsl:version CDATA #FIXED "1.0"
            xmlns:xsl CDATA #FIXED "http://www.w3.org/1999/XSL/Transform">

<!ENTITY ent "The quick brown fox jumped over the lazy dog">
]>

<!-- This tests both AVT's in single-template stylesheets and multiple attribute children -->
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" attr="{//first-name}&ent;{//last-name}"/>
