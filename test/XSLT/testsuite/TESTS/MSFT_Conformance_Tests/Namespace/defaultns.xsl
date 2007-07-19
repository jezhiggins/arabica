<stylesheet xmlns='http://www.w3.org/1999/XSL/Transform' version="1.0">  
<output method="xml" omit-xml-declaration="yes" /> 

<template match="/">  
<if test="//DOCUMENT[TAG1 = TAG2]">  
<value-of select="//DOCUMENT/TAG1"/>  
</if>  

<if test="//DOCUMENT[TAG3 = TAG4/TAG5]">  
<value-of select="//TAG4/text()"/>  
</if>  
</template>  
</stylesheet>  


