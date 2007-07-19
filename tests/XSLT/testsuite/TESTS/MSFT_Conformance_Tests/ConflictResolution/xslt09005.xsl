<stylesheet xmlns="http://www.w3.org/1999/XSL/Transform" version="1.0" 

xmlns:my="urn:http//www.placeholder-name-here.com/schema/">
 


 <template match="/">
	
		<apply-templates/>
	
 </template>
<template match="magazine/title">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="*">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

  <template match="*" priority="-1">
	<my:SPAN style="color=red" > BUG
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="magazine/title">
	<my:SPAN style="color=brown" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp1">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp2">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>

<template match="text()" priority="-20">
<apply-templates/>
</template>
<template match="book/title" name="title_temp3">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp4">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp5">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp6">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp7">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp8">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp9">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp10">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp11">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp12">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp13">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp14">
	<my:SPAN style="color=red" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>
<template match="book/title" name="title_temp15">
	<my:SPAN style="color=green" >
<value-of select="name()"/>: <value-of select="."/> </my:SPAN>
<my:br/><apply-templates/>
  </template>


<template match="*">
	<apply-templates/>
  </template>
</stylesheet>
