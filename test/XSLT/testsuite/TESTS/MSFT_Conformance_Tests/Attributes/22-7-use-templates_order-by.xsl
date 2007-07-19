<?xml version='1.0' ?>

<stylesheet xmlns='http://www.w3.org/1999/XSL/Transform' version='1.0'>
<output method="xml" omit-xml-declaration="yes"/>
<template match="/">
	<apply-templates select="//*">
		<sort select="3434" />		
	</apply-templates>
</template>

<template match="*">
	<value-of select="."/>
</template>
</stylesheet>