#ifndef test_suite_DOM_Level_1_Core_Test_Suite
#define test_suite_DOM_Level_1_Core_Test_Suite


/*
This C++ source file was generated for Arabica
from the source document contained in the W3C
DOM Conformance Test Suite.
The source document contained the following notice:


Copyright (c) 2001-2004 World Wide Web Consortium,
(Massachusetts Institute of Technology, Institut National de
Recherche en Informatique et en Automatique, Keio University). All
Rights Reserved. This program is distributed under the W3C's Software
Intellectual Property License. This program is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.
See W3C License http://www.w3.org/Consortium/Legal/ for more details.

*/
#include "dom_conf_test.hpp"
#include "attrcreatedocumentfragment.hpp"
#include "attrcreatetextnode.hpp"
#include "attrcreatetextnode2.hpp"
#include "attrdefaultvalue.hpp"
#include "attreffectivevalue.hpp"
#include "attrentityreplacement.hpp"
#include "attrname.hpp"
#include "attrnextsiblingnull.hpp"
#include "attrnotspecifiedvalue.hpp"
#include "attrparentnodenull.hpp"
#include "attrprevioussiblingnull.hpp"
#include "attrsetvaluenomodificationallowederr.hpp"
#include "attrsetvaluenomodificationallowederrEE.hpp"
#include "attrspecifiedvalue.hpp"
#include "attrspecifiedvaluechanged.hpp"
#include "attrspecifiedvalueremove.hpp"
#include "cdatasectiongetdata.hpp"
#include "cdatasectionnormalize.hpp"
#include "characterdataappenddata.hpp"
#include "characterdataappenddatagetdata.hpp"
#include "characterdataappenddatanomodificationallowederr.hpp"
#include "characterdataappenddatanomodificationallowederrEE.hpp"
#include "characterdatadeletedatabegining.hpp"
#include "characterdatadeletedataend.hpp"
#include "characterdatadeletedataexceedslength.hpp"
#include "characterdatadeletedatagetlengthanddata.hpp"
#include "characterdatadeletedatamiddle.hpp"
#include "characterdatadeletedatanomodificationallowederr.hpp"
#include "characterdatadeletedatanomodificationallowederrEE.hpp"
#include "characterdatagetdata.hpp"
#include "characterdatagetlength.hpp"
#include "characterdataindexsizeerrdeletedatacountnegative.hpp"
#include "characterdataindexsizeerrdeletedataoffsetgreater.hpp"
#include "characterdataindexsizeerrdeletedataoffsetnegative.hpp"
#include "characterdataindexsizeerrinsertdataoffsetgreater.hpp"
#include "characterdataindexsizeerrinsertdataoffsetnegative.hpp"
#include "characterdataindexsizeerrreplacedatacountnegative.hpp"
#include "characterdataindexsizeerrreplacedataoffsetgreater.hpp"
#include "characterdataindexsizeerrreplacedataoffsetnegative.hpp"
#include "characterdataindexsizeerrsubstringcountnegative.hpp"
#include "characterdataindexsizeerrsubstringnegativeoffset.hpp"
#include "characterdataindexsizeerrsubstringoffsetgreater.hpp"
#include "characterdatainsertdatabeginning.hpp"
#include "characterdatainsertdataend.hpp"
#include "characterdatainsertdatamiddle.hpp"
#include "characterdatainsertdatanomodificationallowederr.hpp"
#include "characterdatainsertdatanomodificationallowederrEE.hpp"
#include "characterdatareplacedatabegining.hpp"
#include "characterdatareplacedataend.hpp"
#include "characterdatareplacedataexceedslengthofarg.hpp"
#include "characterdatareplacedataexceedslengthofdata.hpp"
#include "characterdatareplacedatamiddle.hpp"
#include "characterdatareplacedatanomodificationallowederr.hpp"
#include "characterdatareplacedatanomodificationallowederrEE.hpp"
#include "characterdatasetdatanomodificationallowederr.hpp"
#include "characterdatasetdatanomodificationallowederrEE.hpp"
#include "characterdatasetnodevalue.hpp"
#include "characterdatasubstringexceedsvalue.hpp"
#include "characterdatasubstringvalue.hpp"
#include "commentgetcomment.hpp"
#include "documentcreateattribute.hpp"
#include "documentcreatecdatasection.hpp"
#include "documentcreatecomment.hpp"
#include "documentcreatedocumentfragment.hpp"
#include "documentcreateelement.hpp"
#include "documentcreateelementcasesensitive.hpp"
#include "documentcreateelementdefaultattr.hpp"
#include "documentcreateentityreference.hpp"
#include "documentcreateentityreferenceknown.hpp"
#include "documentcreateprocessinginstruction.hpp"
#include "documentcreatetextnode.hpp"
#include "documentgetdoctype.hpp"
#include "documentgetdoctypenodtd.hpp"
#include "documentgetelementsbytagnamelength.hpp"
#include "documentgetelementsbytagnametotallength.hpp"
#include "documentgetelementsbytagnamevalue.hpp"
#include "documentgetimplementation.hpp"
#include "documentgetrootnode.hpp"
#include "documentinvalidcharacterexceptioncreateattribute.hpp"
#include "documentinvalidcharacterexceptioncreateelement.hpp"
#include "documentinvalidcharacterexceptioncreateentref.hpp"
#include "documentinvalidcharacterexceptioncreateentref1.hpp"
#include "documentinvalidcharacterexceptioncreatepi.hpp"
#include "documentinvalidcharacterexceptioncreatepi1.hpp"
#include "documenttypegetdoctype.hpp"
#include "documenttypegetentities.hpp"
#include "documenttypegetentitieslength.hpp"
#include "documenttypegetentitiestype.hpp"
#include "documenttypegetnotations.hpp"
#include "documenttypegetnotationstype.hpp"
#include "domimplementationfeaturenoversion.hpp"
#include "domimplementationfeaturenull.hpp"
#include "domimplementationfeaturexml.hpp"
#include "elementaddnewattribute.hpp"
#include "elementassociatedattribute.hpp"
#include "elementchangeattributevalue.hpp"
#include "elementcreatenewattribute.hpp"
#include "elementgetattributenode.hpp"
#include "elementgetattributenodenull.hpp"
#include "elementgetelementempty.hpp"
#include "elementgetelementsbytagname.hpp"
#include "elementgetelementsbytagnameaccessnodelist.hpp"
#include "elementgetelementsbytagnamenomatch.hpp"
#include "elementgetelementsbytagnamespecialvalue.hpp"
#include "elementgettagname.hpp"
#include "elementinuseattributeerr.hpp"
#include "elementinvalidcharacterexception.hpp"
#include "elementnormalize.hpp"
#include "elementnotfounderr.hpp"
#include "elementremoveattribute.hpp"
#include "elementremoveattributeaftercreate.hpp"
#include "elementremoveattributenode.hpp"
#include "elementremoveattributenodenomodificationallowederr.hpp"
#include "elementremoveattributenodenomodificationallowederrEE.hpp"
#include "elementremoveattributenomodificationallowederr.hpp"
#include "elementremoveattributenomodificationallowederrEE.hpp"
#include "elementremoveattributerestoredefaultvalue.hpp"
#include "elementreplaceattributewithself.hpp"
#include "elementreplaceexistingattribute.hpp"
#include "elementreplaceexistingattributegevalue.hpp"
#include "elementretrieveallattributes.hpp"
#include "elementretrieveattrvalue.hpp"
#include "elementretrievetagname.hpp"
#include "elementsetattributenodenomodificationallowederr.hpp"
#include "elementsetattributenodenomodificationallowederrEE.hpp"
#include "elementsetattributenodenull.hpp"
#include "elementsetattributenomodificationallowederr.hpp"
#include "elementsetattributenomodificationallowederrEE.hpp"
#include "elementwrongdocumenterr.hpp"
#include "entitygetentityname.hpp"
#include "entitygetpublicid.hpp"
#include "entitygetpublicidnull.hpp"
#include "namednodemapchildnoderange.hpp"
#include "namednodemapgetnameditem.hpp"
#include "namednodemapinuseattributeerr.hpp"
#include "namednodemapnotfounderr.hpp"
#include "namednodemapnumberofnodes.hpp"
#include "namednodemapremovenameditem.hpp"
#include "namednodemapremovenameditemgetvalue.hpp"
#include "namednodemapremovenameditemreturnnodevalue.hpp"
#include "namednodemapreturnattrnode.hpp"
#include "namednodemapreturnfirstitem.hpp"
#include "namednodemapreturnlastitem.hpp"
#include "namednodemapreturnnull.hpp"
#include "namednodemapsetnameditem.hpp"
#include "namednodemapsetnameditemreturnvalue.hpp"
#include "namednodemapsetnameditemthatexists.hpp"
#include "namednodemapsetnameditemwithnewvalue.hpp"
#include "namednodemapwrongdocumenterr.hpp"
#include "nodeappendchild.hpp"
#include "nodeappendchildchildexists.hpp"
#include "nodeappendchilddocfragment.hpp"
#include "nodeappendchildgetnodename.hpp"
#include "nodeappendchildinvalidnodetype.hpp"
#include "nodeappendchildnewchilddiffdocument.hpp"
#include "nodeappendchildnodeancestor.hpp"
#include "nodeappendchildnomodificationallowederr.hpp"
#include "nodeappendchildnomodificationallowederrEE.hpp"
#include "nodeattributenodeattribute.hpp"
#include "nodeattributenodename.hpp"
#include "nodeattributenodetype.hpp"
#include "nodeattributenodevalue.hpp"
#include "nodecdatasectionnodeattribute.hpp"
#include "nodecdatasectionnodename.hpp"
#include "nodecdatasectionnodetype.hpp"
#include "nodecdatasectionnodevalue.hpp"
#include "nodechildnodes.hpp"
#include "nodechildnodesappendchild.hpp"
#include "nodechildnodesempty.hpp"
#include "nodecloneattributescopied.hpp"
#include "nodeclonefalsenocopytext.hpp"
#include "nodeclonegetparentnull.hpp"
#include "nodeclonenodefalse.hpp"
#include "nodeclonenodetrue.hpp"
#include "nodeclonetruecopytext.hpp"
#include "nodecommentnodeattributes.hpp"
#include "nodecommentnodename.hpp"
#include "nodecommentnodetype.hpp"
#include "nodecommentnodevalue.hpp"
#include "nodedocumentfragmentnodename.hpp"
#include "nodedocumentfragmentnodetype.hpp"
#include "nodedocumentfragmentnodevalue.hpp"
#include "nodedocumentnodeattribute.hpp"
#include "nodedocumentnodename.hpp"
#include "nodedocumentnodetype.hpp"
#include "nodedocumentnodevalue.hpp"
#include "nodedocumenttypenodename.hpp"
#include "nodedocumenttypenodetype.hpp"
#include "nodedocumenttypenodevalue.hpp"
#include "nodeelementnodeattributes.hpp"
#include "nodeelementnodename.hpp"
#include "nodeelementnodetype.hpp"
#include "nodeelementnodevalue.hpp"
#include "nodeentitynodeattributes.hpp"
#include "nodeentitynodename.hpp"
#include "nodeentitynodetype.hpp"
#include "nodeentitynodevalue.hpp"
#include "nodeentitysetnodevalue.hpp"
#include "nodeentityreferencenodeattributes.hpp"
#include "nodeentityreferencenodename.hpp"
#include "nodeentityreferencenodetype.hpp"
#include "nodeentityreferencenodevalue.hpp"
#include "nodegetfirstchild.hpp"
#include "nodegetfirstchildnull.hpp"
#include "nodegetlastchild.hpp"
#include "nodegetlastchildnull.hpp"
#include "nodegetnextsibling.hpp"
#include "nodegetnextsiblingnull.hpp"
#include "nodegetownerdocument.hpp"
#include "nodegetownerdocumentnull.hpp"
#include "nodegetprevioussibling.hpp"
#include "nodegetprevioussiblingnull.hpp"
#include "nodehaschildnodes.hpp"
#include "nodehaschildnodesfalse.hpp"
#include "nodeinsertbefore.hpp"
#include "nodeinsertbeforedocfragment.hpp"
#include "nodeinsertbeforeinvalidnodetype.hpp"
#include "nodeinsertbeforenewchilddiffdocument.hpp"
#include "nodeinsertbeforenewchildexists.hpp"
#include "nodeinsertbeforenodeancestor.hpp"
#include "nodeinsertbeforenodename.hpp"
#include "nodeinsertbeforenomodificationallowederr.hpp"
#include "nodeinsertbeforenomodificationallowederrEE.hpp"
#include "nodeinsertbeforerefchildnonexistent.hpp"
#include "nodeinsertbeforerefchildnull.hpp"
#include "nodelistindexequalzero.hpp"
#include "nodelistindexgetlength.hpp"
#include "nodelistindexgetlengthofemptylist.hpp"
#include "nodelistindexnotzero.hpp"
#include "nodelistreturnfirstitem.hpp"
#include "nodelistreturnlastitem.hpp"
#include "nodelisttraverselist.hpp"
#include "nodenotationnodeattributes.hpp"
#include "nodenotationnodename.hpp"
#include "nodenotationnodetype.hpp"
#include "nodenotationnodevalue.hpp"
#include "nodeparentnode.hpp"
#include "nodeparentnodenull.hpp"
#include "nodeprocessinginstructionnodeattributes.hpp"
#include "nodeprocessinginstructionnodename.hpp"
#include "nodeprocessinginstructionnodetype.hpp"
#include "nodeprocessinginstructionnodevalue.hpp"
#include "nodeprocessinginstructionsetnodevalue.hpp"
#include "noderemovechild.hpp"
#include "noderemovechildgetnodename.hpp"
#include "noderemovechildnode.hpp"
#include "noderemovechildnomodificationallowederr.hpp"
#include "noderemovechildnomodificationallowederrEE.hpp"
#include "noderemovechildoldchildnonexistent.hpp"
#include "nodereplacechild.hpp"
#include "nodereplacechildinvalidnodetype.hpp"
#include "nodereplacechildnewchilddiffdocument.hpp"
#include "nodereplacechildnewchildexists.hpp"
#include "nodereplacechildnodeancestor.hpp"
#include "nodereplacechildnodename.hpp"
#include "nodereplacechildnomodificationallowederr.hpp"
#include "nodereplacechildnomodificationallowederrEE.hpp"
#include "nodereplacechildoldchildnonexistent.hpp"
#include "nodesetnodevaluenomodificationallowederr.hpp"
#include "nodesetnodevaluenomodificationallowederrEE.hpp"
#include "nodetextnodeattribute.hpp"
#include "nodetextnodename.hpp"
#include "nodetextnodetype.hpp"
#include "nodetextnodevalue.hpp"
#include "notationgetnotationname.hpp"
#include "notationgetpublicid.hpp"
#include "notationgetpublicidnull.hpp"
#include "notationgetsystemid.hpp"
#include "notationgetsystemidnull.hpp"
#include "processinginstructiongetdata.hpp"
#include "processinginstructiongettarget.hpp"
#include "processinginstructionsetdatanomodificationallowederr.hpp"
#include "processinginstructionsetdatanomodificationallowederrEE.hpp"
#include "textindexsizeerrnegativeoffset.hpp"
#include "textindexsizeerroffsetoutofbounds.hpp"
#include "textparseintolistofelements.hpp"
#include "textsplittextfour.hpp"
#include "textsplittextnomodificationallowederr.hpp"
#include "textsplittextnomodificationallowederrEE.hpp"
#include "textsplittextone.hpp"
#include "textsplittextthree.hpp"
#include "textsplittexttwo.hpp"
#include "textwithnomarkup.hpp"
#include "nodevalue01.hpp"
#include "nodevalue02.hpp"
#include "nodevalue03.hpp"
#include "nodevalue04.hpp"
#include "nodevalue05.hpp"
#include "nodevalue06.hpp"
#include "nodevalue07.hpp"
#include "nodevalue08.hpp"
#include "nodevalue09.hpp"
#include "hc_attrcreatedocumentfragment.hpp"
#include "hc_attrcreatetextnode.hpp"
#include "hc_attrcreatetextnode2.hpp"
#include "hc_attreffectivevalue.hpp"
#include "hc_attrname.hpp"
#include "hc_attrnextsiblingnull.hpp"
#include "hc_attrparentnodenull.hpp"
#include "hc_attrprevioussiblingnull.hpp"
#include "hc_attrspecifiedvalue.hpp"
#include "hc_attrspecifiedvaluechanged.hpp"
#include "hc_characterdataappenddata.hpp"
#include "hc_characterdataappenddatagetdata.hpp"
#include "hc_characterdatadeletedatabegining.hpp"
#include "hc_characterdatadeletedataend.hpp"
#include "hc_characterdatadeletedataexceedslength.hpp"
#include "hc_characterdatadeletedatagetlengthanddata.hpp"
#include "hc_characterdatadeletedatamiddle.hpp"
#include "hc_characterdatagetdata.hpp"
#include "hc_characterdatagetlength.hpp"
#include "hc_characterdataindexsizeerrdeletedatacountnegative.hpp"
#include "hc_characterdataindexsizeerrdeletedataoffsetgreater.hpp"
#include "hc_characterdataindexsizeerrdeletedataoffsetnegative.hpp"
#include "hc_characterdataindexsizeerrinsertdataoffsetgreater.hpp"
#include "hc_characterdataindexsizeerrinsertdataoffsetnegative.hpp"
#include "hc_characterdataindexsizeerrreplacedatacountnegative.hpp"
#include "hc_characterdataindexsizeerrreplacedataoffsetgreater.hpp"
#include "hc_characterdataindexsizeerrreplacedataoffsetnegative.hpp"
#include "hc_characterdataindexsizeerrsubstringcountnegative.hpp"
#include "hc_characterdataindexsizeerrsubstringnegativeoffset.hpp"
#include "hc_characterdataindexsizeerrsubstringoffsetgreater.hpp"
#include "hc_characterdatainsertdatabeginning.hpp"
#include "hc_characterdatainsertdataend.hpp"
#include "hc_characterdatainsertdatamiddle.hpp"
#include "hc_characterdatareplacedatabegining.hpp"
#include "hc_characterdatareplacedataend.hpp"
#include "hc_characterdatareplacedataexceedslengthofarg.hpp"
#include "hc_characterdatareplacedataexceedslengthofdata.hpp"
#include "hc_characterdatareplacedatamiddle.hpp"
#include "hc_characterdatasetnodevalue.hpp"
#include "hc_characterdatasubstringexceedsvalue.hpp"
#include "hc_characterdatasubstringvalue.hpp"
#include "hc_commentgetcomment.hpp"
#include "hc_documentcreateattribute.hpp"
#include "hc_documentcreatecomment.hpp"
#include "hc_documentcreatedocumentfragment.hpp"
#include "hc_documentcreateelement.hpp"
#include "hc_documentcreateelementcasesensitive.hpp"
#include "hc_documentcreatetextnode.hpp"
#include "hc_documentgetdoctype.hpp"
#include "hc_documentgetelementsbytagnamelength.hpp"
#include "hc_documentgetelementsbytagnametotallength.hpp"
#include "hc_documentgetelementsbytagnamevalue.hpp"
#include "hc_documentgetimplementation.hpp"
#include "hc_documentgetrootnode.hpp"
#include "hc_documentinvalidcharacterexceptioncreateattribute.hpp"
#include "hc_documentinvalidcharacterexceptioncreateattribute1.hpp"
#include "hc_documentinvalidcharacterexceptioncreateelement.hpp"
#include "hc_documentinvalidcharacterexceptioncreateelement1.hpp"
#include "hc_domimplementationfeaturenoversion.hpp"
#include "hc_domimplementationfeaturenull.hpp"
#include "hc_domimplementationfeaturexml.hpp"
#include "hc_elementaddnewattribute.hpp"
#include "hc_elementassociatedattribute.hpp"
#include "hc_elementchangeattributevalue.hpp"
#include "hc_elementcreatenewattribute.hpp"
#include "hc_elementgetattributenode.hpp"
#include "hc_elementgetattributenodenull.hpp"
#include "hc_elementgetelementempty.hpp"
#include "hc_elementgetelementsbytagname.hpp"
#include "hc_elementgetelementsbytagnameaccessnodelist.hpp"
#include "hc_elementgetelementsbytagnamenomatch.hpp"
#include "hc_elementgetelementsbytagnamespecialvalue.hpp"
#include "hc_elementgettagname.hpp"
#include "hc_elementinuseattributeerr.hpp"
#include "hc_elementinvalidcharacterexception.hpp"
#include "hc_elementinvalidcharacterexception1.hpp"
#include "hc_elementnormalize.hpp"
#include "hc_elementnormalize2.hpp"
#include "hc_elementnotfounderr.hpp"
#include "hc_elementremoveattribute.hpp"
#include "hc_elementremoveattributeaftercreate.hpp"
#include "hc_elementremoveattributenode.hpp"
#include "hc_elementreplaceattributewithself.hpp"
#include "hc_elementreplaceexistingattribute.hpp"
#include "hc_elementreplaceexistingattributegevalue.hpp"
#include "hc_elementretrieveallattributes.hpp"
#include "hc_elementretrieveattrvalue.hpp"
#include "hc_elementretrievetagname.hpp"
#include "hc_elementsetattributenodenull.hpp"
#include "hc_elementwrongdocumenterr.hpp"
#include "hc_entitiesremovenameditem1.hpp"
#include "hc_entitiessetnameditem1.hpp"
#include "hc_namednodemapchildnoderange.hpp"
#include "hc_namednodemapgetnameditem.hpp"
#include "hc_namednodemapinuseattributeerr.hpp"
#include "hc_namednodemapnotfounderr.hpp"
#include "hc_namednodemapnumberofnodes.hpp"
#include "hc_namednodemapremovenameditem.hpp"
#include "hc_namednodemapreturnattrnode.hpp"
#include "hc_namednodemapreturnfirstitem.hpp"
#include "hc_namednodemapreturnlastitem.hpp"
#include "hc_namednodemapreturnnull.hpp"
#include "hc_namednodemapsetnameditem.hpp"
#include "hc_namednodemapsetnameditemreturnvalue.hpp"
#include "hc_namednodemapsetnameditemthatexists.hpp"
#include "hc_namednodemapsetnameditemwithnewvalue.hpp"
#include "hc_namednodemapwrongdocumenterr.hpp"
#include "hc_nodeappendchild.hpp"
#include "hc_nodeappendchildchildexists.hpp"
#include "hc_nodeappendchilddocfragment.hpp"
#include "hc_nodeappendchildgetnodename.hpp"
#include "hc_nodeappendchildinvalidnodetype.hpp"
#include "hc_nodeappendchildnewchilddiffdocument.hpp"
#include "hc_nodeappendchildnodeancestor.hpp"
#include "hc_nodeattributenodeattribute.hpp"
#include "hc_nodeattributenodename.hpp"
#include "hc_nodeattributenodetype.hpp"
#include "hc_nodeattributenodevalue.hpp"
#include "hc_nodechildnodes.hpp"
#include "hc_nodechildnodesappendchild.hpp"
#include "hc_nodechildnodesempty.hpp"
#include "hc_nodecloneattributescopied.hpp"
#include "hc_nodeclonefalsenocopytext.hpp"
#include "hc_nodeclonegetparentnull.hpp"
#include "hc_nodeclonenodefalse.hpp"
#include "hc_nodeclonenodetrue.hpp"
#include "hc_nodeclonetruecopytext.hpp"
#include "hc_nodecommentnodeattributes.hpp"
#include "hc_nodecommentnodename.hpp"
#include "hc_nodecommentnodetype.hpp"
#include "hc_nodecommentnodevalue.hpp"
#include "hc_nodedocumentfragmentnodename.hpp"
#include "hc_nodedocumentfragmentnodetype.hpp"
#include "hc_nodedocumentfragmentnodevalue.hpp"
#include "hc_nodedocumentnodeattribute.hpp"
#include "hc_nodedocumentnodename.hpp"
#include "hc_nodedocumentnodetype.hpp"
#include "hc_nodedocumentnodevalue.hpp"
#include "hc_nodeelementnodeattributes.hpp"
#include "hc_nodeelementnodename.hpp"
#include "hc_nodeelementnodetype.hpp"
#include "hc_nodeelementnodevalue.hpp"
#include "hc_nodegetfirstchild.hpp"
#include "hc_nodegetfirstchildnull.hpp"
#include "hc_nodegetlastchild.hpp"
#include "hc_nodegetlastchildnull.hpp"
#include "hc_nodegetnextsibling.hpp"
#include "hc_nodegetnextsiblingnull.hpp"
#include "hc_nodegetownerdocument.hpp"
#include "hc_nodegetownerdocumentnull.hpp"
#include "hc_nodegetprevioussibling.hpp"
#include "hc_nodegetprevioussiblingnull.hpp"
#include "hc_nodehaschildnodes.hpp"
#include "hc_nodehaschildnodesfalse.hpp"
#include "hc_nodeinsertbefore.hpp"
#include "hc_nodeinsertbeforedocfragment.hpp"
#include "hc_nodeinsertbeforeinvalidnodetype.hpp"
#include "hc_nodeinsertbeforenewchilddiffdocument.hpp"
#include "hc_nodeinsertbeforenewchildexists.hpp"
#include "hc_nodeinsertbeforenodeancestor.hpp"
#include "hc_nodeinsertbeforenodename.hpp"
#include "hc_nodeinsertbeforerefchildnonexistent.hpp"
#include "hc_nodeinsertbeforerefchildnull.hpp"
#include "hc_nodelistindexequalzero.hpp"
#include "hc_nodelistindexgetlength.hpp"
#include "hc_nodelistindexgetlengthofemptylist.hpp"
#include "hc_nodelistindexnotzero.hpp"
#include "hc_nodelistreturnfirstitem.hpp"
#include "hc_nodelistreturnlastitem.hpp"
#include "hc_nodelisttraverselist.hpp"
#include "hc_nodeparentnode.hpp"
#include "hc_nodeparentnodenull.hpp"
#include "hc_noderemovechild.hpp"
#include "hc_noderemovechildgetnodename.hpp"
#include "hc_noderemovechildnode.hpp"
#include "hc_noderemovechildoldchildnonexistent.hpp"
#include "hc_nodereplacechild.hpp"
#include "hc_nodereplacechildinvalidnodetype.hpp"
#include "hc_nodereplacechildnewchilddiffdocument.hpp"
#include "hc_nodereplacechildnewchildexists.hpp"
#include "hc_nodereplacechildnodeancestor.hpp"
#include "hc_nodereplacechildnodename.hpp"
#include "hc_nodereplacechildoldchildnonexistent.hpp"
#include "hc_nodetextnodeattribute.hpp"
#include "hc_nodetextnodename.hpp"
#include "hc_nodetextnodetype.hpp"
#include "hc_nodetextnodevalue.hpp"
#include "hc_nodevalue01.hpp"
#include "hc_nodevalue02.hpp"
#include "hc_nodevalue03.hpp"
#include "hc_nodevalue04.hpp"
#include "hc_nodevalue05.hpp"
#include "hc_nodevalue06.hpp"
#include "hc_nodevalue07.hpp"
#include "hc_nodevalue08.hpp"
#include "hc_notationsremovenameditem1.hpp"
#include "hc_notationssetnameditem1.hpp"
#include "hc_textindexsizeerrnegativeoffset.hpp"
#include "hc_textindexsizeerroffsetoutofbounds.hpp"
#include "hc_textparseintolistofelements.hpp"
#include "hc_textsplittextfour.hpp"
#include "hc_textsplittextone.hpp"
#include "hc_textsplittextthree.hpp"
#include "hc_textsplittexttwo.hpp"
#include "hc_textwithnomarkup.hpp"
#include "hc_attrappendchild1.hpp"
#include "hc_attrappendchild2.hpp"
#include "hc_attrappendchild3.hpp"
#include "hc_attrappendchild4.hpp"
#include "hc_attrappendchild5.hpp"
#include "hc_attrappendchild6.hpp"
#include "hc_attrchildnodes1.hpp"
#include "hc_attrchildnodes2.hpp"
#include "hc_attrclonenode1.hpp"
#include "hc_attrfirstchild.hpp"
#include "hc_attrgetvalue1.hpp"
#include "hc_attrgetvalue2.hpp"
#include "hc_attrhaschildnodes.hpp"
#include "hc_attrinsertbefore1.hpp"
#include "hc_attrinsertbefore2.hpp"
#include "hc_attrinsertbefore3.hpp"
#include "hc_attrinsertbefore4.hpp"
#include "hc_attrinsertbefore5.hpp"
#include "hc_attrinsertbefore6.hpp"
#include "hc_attrinsertbefore7.hpp"
#include "hc_attrlastchild.hpp"
#include "hc_attrnormalize.hpp"
#include "hc_attrremovechild1.hpp"
#include "hc_attrremovechild2.hpp"
#include "hc_attrreplacechild1.hpp"
#include "hc_attrreplacechild2.hpp"
#include "hc_attrsetvalue1.hpp"
#include "hc_attrsetvalue2.hpp"
#include "attrremovechild1.hpp"
#include "attrreplacechild1.hpp"

template<class string_type, class string_adaptor>
TestSuite* DOM_Level_1_Core_Test_Suite()
{
  TestSuite* suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<attrcreatedocumentfragment<string_type, string_adaptor> >("attrcreatedocumentfragment::test", &attrcreatedocumentfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrcreatetextnode<string_type, string_adaptor> >("attrcreatetextnode::test", &attrcreatetextnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrcreatetextnode2<string_type, string_adaptor> >("attrcreatetextnode2::test", &attrcreatetextnode2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrdefaultvalue<string_type, string_adaptor> >("attrdefaultvalue::test", &attrdefaultvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attreffectivevalue<string_type, string_adaptor> >("attreffectivevalue::test", &attreffectivevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrentityreplacement<string_type, string_adaptor> >("attrentityreplacement::test", &attrentityreplacement<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrname<string_type, string_adaptor> >("attrname::test", &attrname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrnextsiblingnull<string_type, string_adaptor> >("attrnextsiblingnull::test", &attrnextsiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrnotspecifiedvalue<string_type, string_adaptor> >("attrnotspecifiedvalue::test", &attrnotspecifiedvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrparentnodenull<string_type, string_adaptor> >("attrparentnodenull::test", &attrparentnodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrprevioussiblingnull<string_type, string_adaptor> >("attrprevioussiblingnull::test", &attrprevioussiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrsetvaluenomodificationallowederr<string_type, string_adaptor> >("attrsetvaluenomodificationallowederr::test", &attrsetvaluenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrsetvaluenomodificationallowederrEE<string_type, string_adaptor> >("attrsetvaluenomodificationallowederrEE::test", &attrsetvaluenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrspecifiedvalue<string_type, string_adaptor> >("attrspecifiedvalue::test", &attrspecifiedvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrspecifiedvaluechanged<string_type, string_adaptor> >("attrspecifiedvaluechanged::test", &attrspecifiedvaluechanged<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrspecifiedvalueremove<string_type, string_adaptor> >("attrspecifiedvalueremove::test", &attrspecifiedvalueremove<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<cdatasectiongetdata<string_type, string_adaptor> >("cdatasectiongetdata::test", &cdatasectiongetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<cdatasectionnormalize<string_type, string_adaptor> >("cdatasectionnormalize::test", &cdatasectionnormalize<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataappenddata<string_type, string_adaptor> >("characterdataappenddata::test", &characterdataappenddata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataappenddatagetdata<string_type, string_adaptor> >("characterdataappenddatagetdata::test", &characterdataappenddatagetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataappenddatanomodificationallowederr<string_type, string_adaptor> >("characterdataappenddatanomodificationallowederr::test", &characterdataappenddatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataappenddatanomodificationallowederrEE<string_type, string_adaptor> >("characterdataappenddatanomodificationallowederrEE::test", &characterdataappenddatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedatabegining<string_type, string_adaptor> >("characterdatadeletedatabegining::test", &characterdatadeletedatabegining<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedataend<string_type, string_adaptor> >("characterdatadeletedataend::test", &characterdatadeletedataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedataexceedslength<string_type, string_adaptor> >("characterdatadeletedataexceedslength::test", &characterdatadeletedataexceedslength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedatagetlengthanddata<string_type, string_adaptor> >("characterdatadeletedatagetlengthanddata::test", &characterdatadeletedatagetlengthanddata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedatamiddle<string_type, string_adaptor> >("characterdatadeletedatamiddle::test", &characterdatadeletedatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedatanomodificationallowederr<string_type, string_adaptor> >("characterdatadeletedatanomodificationallowederr::test", &characterdatadeletedatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatadeletedatanomodificationallowederrEE<string_type, string_adaptor> >("characterdatadeletedatanomodificationallowederrEE::test", &characterdatadeletedatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatagetdata<string_type, string_adaptor> >("characterdatagetdata::test", &characterdatagetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatagetlength<string_type, string_adaptor> >("characterdatagetlength::test", &characterdatagetlength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrdeletedatacountnegative<string_type, string_adaptor> >("characterdataindexsizeerrdeletedatacountnegative::test", &characterdataindexsizeerrdeletedatacountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrdeletedataoffsetgreater<string_type, string_adaptor> >("characterdataindexsizeerrdeletedataoffsetgreater::test", &characterdataindexsizeerrdeletedataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrdeletedataoffsetnegative<string_type, string_adaptor> >("characterdataindexsizeerrdeletedataoffsetnegative::test", &characterdataindexsizeerrdeletedataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrinsertdataoffsetgreater<string_type, string_adaptor> >("characterdataindexsizeerrinsertdataoffsetgreater::test", &characterdataindexsizeerrinsertdataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrinsertdataoffsetnegative<string_type, string_adaptor> >("characterdataindexsizeerrinsertdataoffsetnegative::test", &characterdataindexsizeerrinsertdataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrreplacedatacountnegative<string_type, string_adaptor> >("characterdataindexsizeerrreplacedatacountnegative::test", &characterdataindexsizeerrreplacedatacountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrreplacedataoffsetgreater<string_type, string_adaptor> >("characterdataindexsizeerrreplacedataoffsetgreater::test", &characterdataindexsizeerrreplacedataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrreplacedataoffsetnegative<string_type, string_adaptor> >("characterdataindexsizeerrreplacedataoffsetnegative::test", &characterdataindexsizeerrreplacedataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrsubstringcountnegative<string_type, string_adaptor> >("characterdataindexsizeerrsubstringcountnegative::test", &characterdataindexsizeerrsubstringcountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrsubstringnegativeoffset<string_type, string_adaptor> >("characterdataindexsizeerrsubstringnegativeoffset::test", &characterdataindexsizeerrsubstringnegativeoffset<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdataindexsizeerrsubstringoffsetgreater<string_type, string_adaptor> >("characterdataindexsizeerrsubstringoffsetgreater::test", &characterdataindexsizeerrsubstringoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatainsertdatabeginning<string_type, string_adaptor> >("characterdatainsertdatabeginning::test", &characterdatainsertdatabeginning<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatainsertdataend<string_type, string_adaptor> >("characterdatainsertdataend::test", &characterdatainsertdataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatainsertdatamiddle<string_type, string_adaptor> >("characterdatainsertdatamiddle::test", &characterdatainsertdatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatainsertdatanomodificationallowederr<string_type, string_adaptor> >("characterdatainsertdatanomodificationallowederr::test", &characterdatainsertdatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatainsertdatanomodificationallowederrEE<string_type, string_adaptor> >("characterdatainsertdatanomodificationallowederrEE::test", &characterdatainsertdatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedatabegining<string_type, string_adaptor> >("characterdatareplacedatabegining::test", &characterdatareplacedatabegining<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedataend<string_type, string_adaptor> >("characterdatareplacedataend::test", &characterdatareplacedataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedataexceedslengthofarg<string_type, string_adaptor> >("characterdatareplacedataexceedslengthofarg::test", &characterdatareplacedataexceedslengthofarg<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedataexceedslengthofdata<string_type, string_adaptor> >("characterdatareplacedataexceedslengthofdata::test", &characterdatareplacedataexceedslengthofdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedatamiddle<string_type, string_adaptor> >("characterdatareplacedatamiddle::test", &characterdatareplacedatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedatanomodificationallowederr<string_type, string_adaptor> >("characterdatareplacedatanomodificationallowederr::test", &characterdatareplacedatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatareplacedatanomodificationallowederrEE<string_type, string_adaptor> >("characterdatareplacedatanomodificationallowederrEE::test", &characterdatareplacedatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatasetdatanomodificationallowederr<string_type, string_adaptor> >("characterdatasetdatanomodificationallowederr::test", &characterdatasetdatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatasetdatanomodificationallowederrEE<string_type, string_adaptor> >("characterdatasetdatanomodificationallowederrEE::test", &characterdatasetdatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatasetnodevalue<string_type, string_adaptor> >("characterdatasetnodevalue::test", &characterdatasetnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatasubstringexceedsvalue<string_type, string_adaptor> >("characterdatasubstringexceedsvalue::test", &characterdatasubstringexceedsvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<characterdatasubstringvalue<string_type, string_adaptor> >("characterdatasubstringvalue::test", &characterdatasubstringvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<commentgetcomment<string_type, string_adaptor> >("commentgetcomment::test", &commentgetcomment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateattribute<string_type, string_adaptor> >("documentcreateattribute::test", &documentcreateattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreatecdatasection<string_type, string_adaptor> >("documentcreatecdatasection::test", &documentcreatecdatasection<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreatecomment<string_type, string_adaptor> >("documentcreatecomment::test", &documentcreatecomment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreatedocumentfragment<string_type, string_adaptor> >("documentcreatedocumentfragment::test", &documentcreatedocumentfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateelement<string_type, string_adaptor> >("documentcreateelement::test", &documentcreateelement<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateelementcasesensitive<string_type, string_adaptor> >("documentcreateelementcasesensitive::test", &documentcreateelementcasesensitive<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateelementdefaultattr<string_type, string_adaptor> >("documentcreateelementdefaultattr::test", &documentcreateelementdefaultattr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateentityreference<string_type, string_adaptor> >("documentcreateentityreference::test", &documentcreateentityreference<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateentityreferenceknown<string_type, string_adaptor> >("documentcreateentityreferenceknown::test", &documentcreateentityreferenceknown<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreateprocessinginstruction<string_type, string_adaptor> >("documentcreateprocessinginstruction::test", &documentcreateprocessinginstruction<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentcreatetextnode<string_type, string_adaptor> >("documentcreatetextnode::test", &documentcreatetextnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetdoctype<string_type, string_adaptor> >("documentgetdoctype::test", &documentgetdoctype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetdoctypenodtd<string_type, string_adaptor> >("documentgetdoctypenodtd::test", &documentgetdoctypenodtd<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetelementsbytagnamelength<string_type, string_adaptor> >("documentgetelementsbytagnamelength::test", &documentgetelementsbytagnamelength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetelementsbytagnametotallength<string_type, string_adaptor> >("documentgetelementsbytagnametotallength::test", &documentgetelementsbytagnametotallength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetelementsbytagnamevalue<string_type, string_adaptor> >("documentgetelementsbytagnamevalue::test", &documentgetelementsbytagnamevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetimplementation<string_type, string_adaptor> >("documentgetimplementation::test", &documentgetimplementation<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentgetrootnode<string_type, string_adaptor> >("documentgetrootnode::test", &documentgetrootnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreateattribute<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreateattribute::test", &documentinvalidcharacterexceptioncreateattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreateelement<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreateelement::test", &documentinvalidcharacterexceptioncreateelement<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreateentref<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreateentref::test", &documentinvalidcharacterexceptioncreateentref<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreateentref1<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreateentref1::test", &documentinvalidcharacterexceptioncreateentref1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreatepi<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreatepi::test", &documentinvalidcharacterexceptioncreatepi<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documentinvalidcharacterexceptioncreatepi1<string_type, string_adaptor> >("documentinvalidcharacterexceptioncreatepi1::test", &documentinvalidcharacterexceptioncreatepi1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetdoctype<string_type, string_adaptor> >("documenttypegetdoctype::test", &documenttypegetdoctype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetentities<string_type, string_adaptor> >("documenttypegetentities::test", &documenttypegetentities<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetentitieslength<string_type, string_adaptor> >("documenttypegetentitieslength::test", &documenttypegetentitieslength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetentitiestype<string_type, string_adaptor> >("documenttypegetentitiestype::test", &documenttypegetentitiestype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetnotations<string_type, string_adaptor> >("documenttypegetnotations::test", &documenttypegetnotations<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<documenttypegetnotationstype<string_type, string_adaptor> >("documenttypegetnotationstype::test", &documenttypegetnotationstype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<domimplementationfeaturenoversion<string_type, string_adaptor> >("domimplementationfeaturenoversion::test", &domimplementationfeaturenoversion<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<domimplementationfeaturenull<string_type, string_adaptor> >("domimplementationfeaturenull::test", &domimplementationfeaturenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<domimplementationfeaturexml<string_type, string_adaptor> >("domimplementationfeaturexml::test", &domimplementationfeaturexml<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementaddnewattribute<string_type, string_adaptor> >("elementaddnewattribute::test", &elementaddnewattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementassociatedattribute<string_type, string_adaptor> >("elementassociatedattribute::test", &elementassociatedattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementchangeattributevalue<string_type, string_adaptor> >("elementchangeattributevalue::test", &elementchangeattributevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementcreatenewattribute<string_type, string_adaptor> >("elementcreatenewattribute::test", &elementcreatenewattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetattributenode<string_type, string_adaptor> >("elementgetattributenode::test", &elementgetattributenode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetattributenodenull<string_type, string_adaptor> >("elementgetattributenodenull::test", &elementgetattributenodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetelementempty<string_type, string_adaptor> >("elementgetelementempty::test", &elementgetelementempty<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetelementsbytagname<string_type, string_adaptor> >("elementgetelementsbytagname::test", &elementgetelementsbytagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetelementsbytagnameaccessnodelist<string_type, string_adaptor> >("elementgetelementsbytagnameaccessnodelist::test", &elementgetelementsbytagnameaccessnodelist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetelementsbytagnamenomatch<string_type, string_adaptor> >("elementgetelementsbytagnamenomatch::test", &elementgetelementsbytagnamenomatch<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgetelementsbytagnamespecialvalue<string_type, string_adaptor> >("elementgetelementsbytagnamespecialvalue::test", &elementgetelementsbytagnamespecialvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementgettagname<string_type, string_adaptor> >("elementgettagname::test", &elementgettagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementinuseattributeerr<string_type, string_adaptor> >("elementinuseattributeerr::test", &elementinuseattributeerr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementinvalidcharacterexception<string_type, string_adaptor> >("elementinvalidcharacterexception::test", &elementinvalidcharacterexception<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementnormalize<string_type, string_adaptor> >("elementnormalize::test", &elementnormalize<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementnotfounderr<string_type, string_adaptor> >("elementnotfounderr::test", &elementnotfounderr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattribute<string_type, string_adaptor> >("elementremoveattribute::test", &elementremoveattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributeaftercreate<string_type, string_adaptor> >("elementremoveattributeaftercreate::test", &elementremoveattributeaftercreate<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributenode<string_type, string_adaptor> >("elementremoveattributenode::test", &elementremoveattributenode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributenodenomodificationallowederr<string_type, string_adaptor> >("elementremoveattributenodenomodificationallowederr::test", &elementremoveattributenodenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributenodenomodificationallowederrEE<string_type, string_adaptor> >("elementremoveattributenodenomodificationallowederrEE::test", &elementremoveattributenodenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributenomodificationallowederr<string_type, string_adaptor> >("elementremoveattributenomodificationallowederr::test", &elementremoveattributenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributenomodificationallowederrEE<string_type, string_adaptor> >("elementremoveattributenomodificationallowederrEE::test", &elementremoveattributenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementremoveattributerestoredefaultvalue<string_type, string_adaptor> >("elementremoveattributerestoredefaultvalue::test", &elementremoveattributerestoredefaultvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementreplaceattributewithself<string_type, string_adaptor> >("elementreplaceattributewithself::test", &elementreplaceattributewithself<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementreplaceexistingattribute<string_type, string_adaptor> >("elementreplaceexistingattribute::test", &elementreplaceexistingattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementreplaceexistingattributegevalue<string_type, string_adaptor> >("elementreplaceexistingattributegevalue::test", &elementreplaceexistingattributegevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementretrieveallattributes<string_type, string_adaptor> >("elementretrieveallattributes::test", &elementretrieveallattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementretrieveattrvalue<string_type, string_adaptor> >("elementretrieveattrvalue::test", &elementretrieveattrvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementretrievetagname<string_type, string_adaptor> >("elementretrievetagname::test", &elementretrievetagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementsetattributenodenomodificationallowederr<string_type, string_adaptor> >("elementsetattributenodenomodificationallowederr::test", &elementsetattributenodenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementsetattributenodenomodificationallowederrEE<string_type, string_adaptor> >("elementsetattributenodenomodificationallowederrEE::test", &elementsetattributenodenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementsetattributenodenull<string_type, string_adaptor> >("elementsetattributenodenull::test", &elementsetattributenodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementsetattributenomodificationallowederr<string_type, string_adaptor> >("elementsetattributenomodificationallowederr::test", &elementsetattributenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementsetattributenomodificationallowederrEE<string_type, string_adaptor> >("elementsetattributenomodificationallowederrEE::test", &elementsetattributenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<elementwrongdocumenterr<string_type, string_adaptor> >("elementwrongdocumenterr::test", &elementwrongdocumenterr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<entitygetentityname<string_type, string_adaptor> >("entitygetentityname::test", &entitygetentityname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<entitygetpublicid<string_type, string_adaptor> >("entitygetpublicid::test", &entitygetpublicid<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<entitygetpublicidnull<string_type, string_adaptor> >("entitygetpublicidnull::test", &entitygetpublicidnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapchildnoderange<string_type, string_adaptor> >("namednodemapchildnoderange::test", &namednodemapchildnoderange<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapgetnameditem<string_type, string_adaptor> >("namednodemapgetnameditem::test", &namednodemapgetnameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapinuseattributeerr<string_type, string_adaptor> >("namednodemapinuseattributeerr::test", &namednodemapinuseattributeerr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapnotfounderr<string_type, string_adaptor> >("namednodemapnotfounderr::test", &namednodemapnotfounderr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapnumberofnodes<string_type, string_adaptor> >("namednodemapnumberofnodes::test", &namednodemapnumberofnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapremovenameditem<string_type, string_adaptor> >("namednodemapremovenameditem::test", &namednodemapremovenameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapremovenameditemgetvalue<string_type, string_adaptor> >("namednodemapremovenameditemgetvalue::test", &namednodemapremovenameditemgetvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapremovenameditemreturnnodevalue<string_type, string_adaptor> >("namednodemapremovenameditemreturnnodevalue::test", &namednodemapremovenameditemreturnnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapreturnattrnode<string_type, string_adaptor> >("namednodemapreturnattrnode::test", &namednodemapreturnattrnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapreturnfirstitem<string_type, string_adaptor> >("namednodemapreturnfirstitem::test", &namednodemapreturnfirstitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapreturnlastitem<string_type, string_adaptor> >("namednodemapreturnlastitem::test", &namednodemapreturnlastitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapreturnnull<string_type, string_adaptor> >("namednodemapreturnnull::test", &namednodemapreturnnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapsetnameditem<string_type, string_adaptor> >("namednodemapsetnameditem::test", &namednodemapsetnameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapsetnameditemreturnvalue<string_type, string_adaptor> >("namednodemapsetnameditemreturnvalue::test", &namednodemapsetnameditemreturnvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapsetnameditemthatexists<string_type, string_adaptor> >("namednodemapsetnameditemthatexists::test", &namednodemapsetnameditemthatexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapsetnameditemwithnewvalue<string_type, string_adaptor> >("namednodemapsetnameditemwithnewvalue::test", &namednodemapsetnameditemwithnewvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<namednodemapwrongdocumenterr<string_type, string_adaptor> >("namednodemapwrongdocumenterr::test", &namednodemapwrongdocumenterr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchild<string_type, string_adaptor> >("nodeappendchild::test", &nodeappendchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildchildexists<string_type, string_adaptor> >("nodeappendchildchildexists::test", &nodeappendchildchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchilddocfragment<string_type, string_adaptor> >("nodeappendchilddocfragment::test", &nodeappendchilddocfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildgetnodename<string_type, string_adaptor> >("nodeappendchildgetnodename::test", &nodeappendchildgetnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildinvalidnodetype<string_type, string_adaptor> >("nodeappendchildinvalidnodetype::test", &nodeappendchildinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildnewchilddiffdocument<string_type, string_adaptor> >("nodeappendchildnewchilddiffdocument::test", &nodeappendchildnewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildnodeancestor<string_type, string_adaptor> >("nodeappendchildnodeancestor::test", &nodeappendchildnodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildnomodificationallowederr<string_type, string_adaptor> >("nodeappendchildnomodificationallowederr::test", &nodeappendchildnomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeappendchildnomodificationallowederrEE<string_type, string_adaptor> >("nodeappendchildnomodificationallowederrEE::test", &nodeappendchildnomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeattributenodeattribute<string_type, string_adaptor> >("nodeattributenodeattribute::test", &nodeattributenodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeattributenodename<string_type, string_adaptor> >("nodeattributenodename::test", &nodeattributenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeattributenodetype<string_type, string_adaptor> >("nodeattributenodetype::test", &nodeattributenodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeattributenodevalue<string_type, string_adaptor> >("nodeattributenodevalue::test", &nodeattributenodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecdatasectionnodeattribute<string_type, string_adaptor> >("nodecdatasectionnodeattribute::test", &nodecdatasectionnodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecdatasectionnodename<string_type, string_adaptor> >("nodecdatasectionnodename::test", &nodecdatasectionnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecdatasectionnodetype<string_type, string_adaptor> >("nodecdatasectionnodetype::test", &nodecdatasectionnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecdatasectionnodevalue<string_type, string_adaptor> >("nodecdatasectionnodevalue::test", &nodecdatasectionnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodechildnodes<string_type, string_adaptor> >("nodechildnodes::test", &nodechildnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodechildnodesappendchild<string_type, string_adaptor> >("nodechildnodesappendchild::test", &nodechildnodesappendchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodechildnodesempty<string_type, string_adaptor> >("nodechildnodesempty::test", &nodechildnodesempty<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecloneattributescopied<string_type, string_adaptor> >("nodecloneattributescopied::test", &nodecloneattributescopied<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeclonefalsenocopytext<string_type, string_adaptor> >("nodeclonefalsenocopytext::test", &nodeclonefalsenocopytext<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeclonegetparentnull<string_type, string_adaptor> >("nodeclonegetparentnull::test", &nodeclonegetparentnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeclonenodefalse<string_type, string_adaptor> >("nodeclonenodefalse::test", &nodeclonenodefalse<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeclonenodetrue<string_type, string_adaptor> >("nodeclonenodetrue::test", &nodeclonenodetrue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeclonetruecopytext<string_type, string_adaptor> >("nodeclonetruecopytext::test", &nodeclonetruecopytext<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecommentnodeattributes<string_type, string_adaptor> >("nodecommentnodeattributes::test", &nodecommentnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecommentnodename<string_type, string_adaptor> >("nodecommentnodename::test", &nodecommentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecommentnodetype<string_type, string_adaptor> >("nodecommentnodetype::test", &nodecommentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodecommentnodevalue<string_type, string_adaptor> >("nodecommentnodevalue::test", &nodecommentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentfragmentnodename<string_type, string_adaptor> >("nodedocumentfragmentnodename::test", &nodedocumentfragmentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentfragmentnodetype<string_type, string_adaptor> >("nodedocumentfragmentnodetype::test", &nodedocumentfragmentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentfragmentnodevalue<string_type, string_adaptor> >("nodedocumentfragmentnodevalue::test", &nodedocumentfragmentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentnodeattribute<string_type, string_adaptor> >("nodedocumentnodeattribute::test", &nodedocumentnodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentnodename<string_type, string_adaptor> >("nodedocumentnodename::test", &nodedocumentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentnodetype<string_type, string_adaptor> >("nodedocumentnodetype::test", &nodedocumentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumentnodevalue<string_type, string_adaptor> >("nodedocumentnodevalue::test", &nodedocumentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumenttypenodename<string_type, string_adaptor> >("nodedocumenttypenodename::test", &nodedocumenttypenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumenttypenodetype<string_type, string_adaptor> >("nodedocumenttypenodetype::test", &nodedocumenttypenodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodedocumenttypenodevalue<string_type, string_adaptor> >("nodedocumenttypenodevalue::test", &nodedocumenttypenodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeelementnodeattributes<string_type, string_adaptor> >("nodeelementnodeattributes::test", &nodeelementnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeelementnodename<string_type, string_adaptor> >("nodeelementnodename::test", &nodeelementnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeelementnodetype<string_type, string_adaptor> >("nodeelementnodetype::test", &nodeelementnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeelementnodevalue<string_type, string_adaptor> >("nodeelementnodevalue::test", &nodeelementnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentitynodeattributes<string_type, string_adaptor> >("nodeentitynodeattributes::test", &nodeentitynodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentitynodename<string_type, string_adaptor> >("nodeentitynodename::test", &nodeentitynodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentitynodetype<string_type, string_adaptor> >("nodeentitynodetype::test", &nodeentitynodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentitynodevalue<string_type, string_adaptor> >("nodeentitynodevalue::test", &nodeentitynodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentitysetnodevalue<string_type, string_adaptor> >("nodeentitysetnodevalue::test", &nodeentitysetnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentityreferencenodeattributes<string_type, string_adaptor> >("nodeentityreferencenodeattributes::test", &nodeentityreferencenodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentityreferencenodename<string_type, string_adaptor> >("nodeentityreferencenodename::test", &nodeentityreferencenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentityreferencenodetype<string_type, string_adaptor> >("nodeentityreferencenodetype::test", &nodeentityreferencenodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeentityreferencenodevalue<string_type, string_adaptor> >("nodeentityreferencenodevalue::test", &nodeentityreferencenodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetfirstchild<string_type, string_adaptor> >("nodegetfirstchild::test", &nodegetfirstchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetfirstchildnull<string_type, string_adaptor> >("nodegetfirstchildnull::test", &nodegetfirstchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetlastchild<string_type, string_adaptor> >("nodegetlastchild::test", &nodegetlastchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetlastchildnull<string_type, string_adaptor> >("nodegetlastchildnull::test", &nodegetlastchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetnextsibling<string_type, string_adaptor> >("nodegetnextsibling::test", &nodegetnextsibling<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetnextsiblingnull<string_type, string_adaptor> >("nodegetnextsiblingnull::test", &nodegetnextsiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetownerdocument<string_type, string_adaptor> >("nodegetownerdocument::test", &nodegetownerdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetownerdocumentnull<string_type, string_adaptor> >("nodegetownerdocumentnull::test", &nodegetownerdocumentnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetprevioussibling<string_type, string_adaptor> >("nodegetprevioussibling::test", &nodegetprevioussibling<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodegetprevioussiblingnull<string_type, string_adaptor> >("nodegetprevioussiblingnull::test", &nodegetprevioussiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodehaschildnodes<string_type, string_adaptor> >("nodehaschildnodes::test", &nodehaschildnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodehaschildnodesfalse<string_type, string_adaptor> >("nodehaschildnodesfalse::test", &nodehaschildnodesfalse<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbefore<string_type, string_adaptor> >("nodeinsertbefore::test", &nodeinsertbefore<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforedocfragment<string_type, string_adaptor> >("nodeinsertbeforedocfragment::test", &nodeinsertbeforedocfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforeinvalidnodetype<string_type, string_adaptor> >("nodeinsertbeforeinvalidnodetype::test", &nodeinsertbeforeinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenewchilddiffdocument<string_type, string_adaptor> >("nodeinsertbeforenewchilddiffdocument::test", &nodeinsertbeforenewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenewchildexists<string_type, string_adaptor> >("nodeinsertbeforenewchildexists::test", &nodeinsertbeforenewchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenodeancestor<string_type, string_adaptor> >("nodeinsertbeforenodeancestor::test", &nodeinsertbeforenodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenodename<string_type, string_adaptor> >("nodeinsertbeforenodename::test", &nodeinsertbeforenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenomodificationallowederr<string_type, string_adaptor> >("nodeinsertbeforenomodificationallowederr::test", &nodeinsertbeforenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforenomodificationallowederrEE<string_type, string_adaptor> >("nodeinsertbeforenomodificationallowederrEE::test", &nodeinsertbeforenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforerefchildnonexistent<string_type, string_adaptor> >("nodeinsertbeforerefchildnonexistent::test", &nodeinsertbeforerefchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeinsertbeforerefchildnull<string_type, string_adaptor> >("nodeinsertbeforerefchildnull::test", &nodeinsertbeforerefchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistindexequalzero<string_type, string_adaptor> >("nodelistindexequalzero::test", &nodelistindexequalzero<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistindexgetlength<string_type, string_adaptor> >("nodelistindexgetlength::test", &nodelistindexgetlength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistindexgetlengthofemptylist<string_type, string_adaptor> >("nodelistindexgetlengthofemptylist::test", &nodelistindexgetlengthofemptylist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistindexnotzero<string_type, string_adaptor> >("nodelistindexnotzero::test", &nodelistindexnotzero<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistreturnfirstitem<string_type, string_adaptor> >("nodelistreturnfirstitem::test", &nodelistreturnfirstitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelistreturnlastitem<string_type, string_adaptor> >("nodelistreturnlastitem::test", &nodelistreturnlastitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodelisttraverselist<string_type, string_adaptor> >("nodelisttraverselist::test", &nodelisttraverselist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodenotationnodeattributes<string_type, string_adaptor> >("nodenotationnodeattributes::test", &nodenotationnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodenotationnodename<string_type, string_adaptor> >("nodenotationnodename::test", &nodenotationnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodenotationnodetype<string_type, string_adaptor> >("nodenotationnodetype::test", &nodenotationnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodenotationnodevalue<string_type, string_adaptor> >("nodenotationnodevalue::test", &nodenotationnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeparentnode<string_type, string_adaptor> >("nodeparentnode::test", &nodeparentnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeparentnodenull<string_type, string_adaptor> >("nodeparentnodenull::test", &nodeparentnodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeprocessinginstructionnodeattributes<string_type, string_adaptor> >("nodeprocessinginstructionnodeattributes::test", &nodeprocessinginstructionnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeprocessinginstructionnodename<string_type, string_adaptor> >("nodeprocessinginstructionnodename::test", &nodeprocessinginstructionnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeprocessinginstructionnodetype<string_type, string_adaptor> >("nodeprocessinginstructionnodetype::test", &nodeprocessinginstructionnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeprocessinginstructionnodevalue<string_type, string_adaptor> >("nodeprocessinginstructionnodevalue::test", &nodeprocessinginstructionnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodeprocessinginstructionsetnodevalue<string_type, string_adaptor> >("nodeprocessinginstructionsetnodevalue::test", &nodeprocessinginstructionsetnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechild<string_type, string_adaptor> >("noderemovechild::test", &noderemovechild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechildgetnodename<string_type, string_adaptor> >("noderemovechildgetnodename::test", &noderemovechildgetnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechildnode<string_type, string_adaptor> >("noderemovechildnode::test", &noderemovechildnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechildnomodificationallowederr<string_type, string_adaptor> >("noderemovechildnomodificationallowederr::test", &noderemovechildnomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechildnomodificationallowederrEE<string_type, string_adaptor> >("noderemovechildnomodificationallowederrEE::test", &noderemovechildnomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<noderemovechildoldchildnonexistent<string_type, string_adaptor> >("noderemovechildoldchildnonexistent::test", &noderemovechildoldchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechild<string_type, string_adaptor> >("nodereplacechild::test", &nodereplacechild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildinvalidnodetype<string_type, string_adaptor> >("nodereplacechildinvalidnodetype::test", &nodereplacechildinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnewchilddiffdocument<string_type, string_adaptor> >("nodereplacechildnewchilddiffdocument::test", &nodereplacechildnewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnewchildexists<string_type, string_adaptor> >("nodereplacechildnewchildexists::test", &nodereplacechildnewchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnodeancestor<string_type, string_adaptor> >("nodereplacechildnodeancestor::test", &nodereplacechildnodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnodename<string_type, string_adaptor> >("nodereplacechildnodename::test", &nodereplacechildnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnomodificationallowederr<string_type, string_adaptor> >("nodereplacechildnomodificationallowederr::test", &nodereplacechildnomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildnomodificationallowederrEE<string_type, string_adaptor> >("nodereplacechildnomodificationallowederrEE::test", &nodereplacechildnomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodereplacechildoldchildnonexistent<string_type, string_adaptor> >("nodereplacechildoldchildnonexistent::test", &nodereplacechildoldchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodesetnodevaluenomodificationallowederr<string_type, string_adaptor> >("nodesetnodevaluenomodificationallowederr::test", &nodesetnodevaluenomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodesetnodevaluenomodificationallowederrEE<string_type, string_adaptor> >("nodesetnodevaluenomodificationallowederrEE::test", &nodesetnodevaluenomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodetextnodeattribute<string_type, string_adaptor> >("nodetextnodeattribute::test", &nodetextnodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodetextnodename<string_type, string_adaptor> >("nodetextnodename::test", &nodetextnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodetextnodetype<string_type, string_adaptor> >("nodetextnodetype::test", &nodetextnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodetextnodevalue<string_type, string_adaptor> >("nodetextnodevalue::test", &nodetextnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<notationgetnotationname<string_type, string_adaptor> >("notationgetnotationname::test", &notationgetnotationname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<notationgetpublicid<string_type, string_adaptor> >("notationgetpublicid::test", &notationgetpublicid<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<notationgetpublicidnull<string_type, string_adaptor> >("notationgetpublicidnull::test", &notationgetpublicidnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<notationgetsystemid<string_type, string_adaptor> >("notationgetsystemid::test", &notationgetsystemid<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<notationgetsystemidnull<string_type, string_adaptor> >("notationgetsystemidnull::test", &notationgetsystemidnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<processinginstructiongetdata<string_type, string_adaptor> >("processinginstructiongetdata::test", &processinginstructiongetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<processinginstructiongettarget<string_type, string_adaptor> >("processinginstructiongettarget::test", &processinginstructiongettarget<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<processinginstructionsetdatanomodificationallowederr<string_type, string_adaptor> >("processinginstructionsetdatanomodificationallowederr::test", &processinginstructionsetdatanomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<processinginstructionsetdatanomodificationallowederrEE<string_type, string_adaptor> >("processinginstructionsetdatanomodificationallowederrEE::test", &processinginstructionsetdatanomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textindexsizeerrnegativeoffset<string_type, string_adaptor> >("textindexsizeerrnegativeoffset::test", &textindexsizeerrnegativeoffset<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textindexsizeerroffsetoutofbounds<string_type, string_adaptor> >("textindexsizeerroffsetoutofbounds::test", &textindexsizeerroffsetoutofbounds<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textparseintolistofelements<string_type, string_adaptor> >("textparseintolistofelements::test", &textparseintolistofelements<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittextfour<string_type, string_adaptor> >("textsplittextfour::test", &textsplittextfour<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittextnomodificationallowederr<string_type, string_adaptor> >("textsplittextnomodificationallowederr::test", &textsplittextnomodificationallowederr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittextnomodificationallowederrEE<string_type, string_adaptor> >("textsplittextnomodificationallowederrEE::test", &textsplittextnomodificationallowederrEE<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittextone<string_type, string_adaptor> >("textsplittextone::test", &textsplittextone<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittextthree<string_type, string_adaptor> >("textsplittextthree::test", &textsplittextthree<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textsplittexttwo<string_type, string_adaptor> >("textsplittexttwo::test", &textsplittexttwo<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<textwithnomarkup<string_type, string_adaptor> >("textwithnomarkup::test", &textwithnomarkup<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue01<string_type, string_adaptor> >("nodevalue01::test", &nodevalue01<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue02<string_type, string_adaptor> >("nodevalue02::test", &nodevalue02<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue03<string_type, string_adaptor> >("nodevalue03::test", &nodevalue03<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue04<string_type, string_adaptor> >("nodevalue04::test", &nodevalue04<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue05<string_type, string_adaptor> >("nodevalue05::test", &nodevalue05<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue06<string_type, string_adaptor> >("nodevalue06::test", &nodevalue06<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue07<string_type, string_adaptor> >("nodevalue07::test", &nodevalue07<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue08<string_type, string_adaptor> >("nodevalue08::test", &nodevalue08<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<nodevalue09<string_type, string_adaptor> >("nodevalue09::test", &nodevalue09<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrcreatedocumentfragment<string_type, string_adaptor> >("hc_attrcreatedocumentfragment::test", &hc_attrcreatedocumentfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrcreatetextnode<string_type, string_adaptor> >("hc_attrcreatetextnode::test", &hc_attrcreatetextnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrcreatetextnode2<string_type, string_adaptor> >("hc_attrcreatetextnode2::test", &hc_attrcreatetextnode2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attreffectivevalue<string_type, string_adaptor> >("hc_attreffectivevalue::test", &hc_attreffectivevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrname<string_type, string_adaptor> >("hc_attrname::test", &hc_attrname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrnextsiblingnull<string_type, string_adaptor> >("hc_attrnextsiblingnull::test", &hc_attrnextsiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrparentnodenull<string_type, string_adaptor> >("hc_attrparentnodenull::test", &hc_attrparentnodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrprevioussiblingnull<string_type, string_adaptor> >("hc_attrprevioussiblingnull::test", &hc_attrprevioussiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrspecifiedvalue<string_type, string_adaptor> >("hc_attrspecifiedvalue::test", &hc_attrspecifiedvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrspecifiedvaluechanged<string_type, string_adaptor> >("hc_attrspecifiedvaluechanged::test", &hc_attrspecifiedvaluechanged<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataappenddata<string_type, string_adaptor> >("hc_characterdataappenddata::test", &hc_characterdataappenddata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataappenddatagetdata<string_type, string_adaptor> >("hc_characterdataappenddatagetdata::test", &hc_characterdataappenddatagetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatadeletedatabegining<string_type, string_adaptor> >("hc_characterdatadeletedatabegining::test", &hc_characterdatadeletedatabegining<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatadeletedataend<string_type, string_adaptor> >("hc_characterdatadeletedataend::test", &hc_characterdatadeletedataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatadeletedataexceedslength<string_type, string_adaptor> >("hc_characterdatadeletedataexceedslength::test", &hc_characterdatadeletedataexceedslength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatadeletedatagetlengthanddata<string_type, string_adaptor> >("hc_characterdatadeletedatagetlengthanddata::test", &hc_characterdatadeletedatagetlengthanddata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatadeletedatamiddle<string_type, string_adaptor> >("hc_characterdatadeletedatamiddle::test", &hc_characterdatadeletedatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatagetdata<string_type, string_adaptor> >("hc_characterdatagetdata::test", &hc_characterdatagetdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatagetlength<string_type, string_adaptor> >("hc_characterdatagetlength::test", &hc_characterdatagetlength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrdeletedatacountnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrdeletedatacountnegative::test", &hc_characterdataindexsizeerrdeletedatacountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrdeletedataoffsetgreater<string_type, string_adaptor> >("hc_characterdataindexsizeerrdeletedataoffsetgreater::test", &hc_characterdataindexsizeerrdeletedataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrdeletedataoffsetnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrdeletedataoffsetnegative::test", &hc_characterdataindexsizeerrdeletedataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrinsertdataoffsetgreater<string_type, string_adaptor> >("hc_characterdataindexsizeerrinsertdataoffsetgreater::test", &hc_characterdataindexsizeerrinsertdataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrinsertdataoffsetnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrinsertdataoffsetnegative::test", &hc_characterdataindexsizeerrinsertdataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrreplacedatacountnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrreplacedatacountnegative::test", &hc_characterdataindexsizeerrreplacedatacountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrreplacedataoffsetgreater<string_type, string_adaptor> >("hc_characterdataindexsizeerrreplacedataoffsetgreater::test", &hc_characterdataindexsizeerrreplacedataoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrreplacedataoffsetnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrreplacedataoffsetnegative::test", &hc_characterdataindexsizeerrreplacedataoffsetnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrsubstringcountnegative<string_type, string_adaptor> >("hc_characterdataindexsizeerrsubstringcountnegative::test", &hc_characterdataindexsizeerrsubstringcountnegative<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrsubstringnegativeoffset<string_type, string_adaptor> >("hc_characterdataindexsizeerrsubstringnegativeoffset::test", &hc_characterdataindexsizeerrsubstringnegativeoffset<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdataindexsizeerrsubstringoffsetgreater<string_type, string_adaptor> >("hc_characterdataindexsizeerrsubstringoffsetgreater::test", &hc_characterdataindexsizeerrsubstringoffsetgreater<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatainsertdatabeginning<string_type, string_adaptor> >("hc_characterdatainsertdatabeginning::test", &hc_characterdatainsertdatabeginning<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatainsertdataend<string_type, string_adaptor> >("hc_characterdatainsertdataend::test", &hc_characterdatainsertdataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatainsertdatamiddle<string_type, string_adaptor> >("hc_characterdatainsertdatamiddle::test", &hc_characterdatainsertdatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatareplacedatabegining<string_type, string_adaptor> >("hc_characterdatareplacedatabegining::test", &hc_characterdatareplacedatabegining<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatareplacedataend<string_type, string_adaptor> >("hc_characterdatareplacedataend::test", &hc_characterdatareplacedataend<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatareplacedataexceedslengthofarg<string_type, string_adaptor> >("hc_characterdatareplacedataexceedslengthofarg::test", &hc_characterdatareplacedataexceedslengthofarg<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatareplacedataexceedslengthofdata<string_type, string_adaptor> >("hc_characterdatareplacedataexceedslengthofdata::test", &hc_characterdatareplacedataexceedslengthofdata<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatareplacedatamiddle<string_type, string_adaptor> >("hc_characterdatareplacedatamiddle::test", &hc_characterdatareplacedatamiddle<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatasetnodevalue<string_type, string_adaptor> >("hc_characterdatasetnodevalue::test", &hc_characterdatasetnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatasubstringexceedsvalue<string_type, string_adaptor> >("hc_characterdatasubstringexceedsvalue::test", &hc_characterdatasubstringexceedsvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_characterdatasubstringvalue<string_type, string_adaptor> >("hc_characterdatasubstringvalue::test", &hc_characterdatasubstringvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_commentgetcomment<string_type, string_adaptor> >("hc_commentgetcomment::test", &hc_commentgetcomment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreateattribute<string_type, string_adaptor> >("hc_documentcreateattribute::test", &hc_documentcreateattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreatecomment<string_type, string_adaptor> >("hc_documentcreatecomment::test", &hc_documentcreatecomment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreatedocumentfragment<string_type, string_adaptor> >("hc_documentcreatedocumentfragment::test", &hc_documentcreatedocumentfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreateelement<string_type, string_adaptor> >("hc_documentcreateelement::test", &hc_documentcreateelement<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreateelementcasesensitive<string_type, string_adaptor> >("hc_documentcreateelementcasesensitive::test", &hc_documentcreateelementcasesensitive<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentcreatetextnode<string_type, string_adaptor> >("hc_documentcreatetextnode::test", &hc_documentcreatetextnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetdoctype<string_type, string_adaptor> >("hc_documentgetdoctype::test", &hc_documentgetdoctype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetelementsbytagnamelength<string_type, string_adaptor> >("hc_documentgetelementsbytagnamelength::test", &hc_documentgetelementsbytagnamelength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetelementsbytagnametotallength<string_type, string_adaptor> >("hc_documentgetelementsbytagnametotallength::test", &hc_documentgetelementsbytagnametotallength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetelementsbytagnamevalue<string_type, string_adaptor> >("hc_documentgetelementsbytagnamevalue::test", &hc_documentgetelementsbytagnamevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetimplementation<string_type, string_adaptor> >("hc_documentgetimplementation::test", &hc_documentgetimplementation<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentgetrootnode<string_type, string_adaptor> >("hc_documentgetrootnode::test", &hc_documentgetrootnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentinvalidcharacterexceptioncreateattribute<string_type, string_adaptor> >("hc_documentinvalidcharacterexceptioncreateattribute::test", &hc_documentinvalidcharacterexceptioncreateattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentinvalidcharacterexceptioncreateattribute1<string_type, string_adaptor> >("hc_documentinvalidcharacterexceptioncreateattribute1::test", &hc_documentinvalidcharacterexceptioncreateattribute1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentinvalidcharacterexceptioncreateelement<string_type, string_adaptor> >("hc_documentinvalidcharacterexceptioncreateelement::test", &hc_documentinvalidcharacterexceptioncreateelement<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_documentinvalidcharacterexceptioncreateelement1<string_type, string_adaptor> >("hc_documentinvalidcharacterexceptioncreateelement1::test", &hc_documentinvalidcharacterexceptioncreateelement1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_domimplementationfeaturenoversion<string_type, string_adaptor> >("hc_domimplementationfeaturenoversion::test", &hc_domimplementationfeaturenoversion<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_domimplementationfeaturenull<string_type, string_adaptor> >("hc_domimplementationfeaturenull::test", &hc_domimplementationfeaturenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_domimplementationfeaturexml<string_type, string_adaptor> >("hc_domimplementationfeaturexml::test", &hc_domimplementationfeaturexml<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementaddnewattribute<string_type, string_adaptor> >("hc_elementaddnewattribute::test", &hc_elementaddnewattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementassociatedattribute<string_type, string_adaptor> >("hc_elementassociatedattribute::test", &hc_elementassociatedattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementchangeattributevalue<string_type, string_adaptor> >("hc_elementchangeattributevalue::test", &hc_elementchangeattributevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementcreatenewattribute<string_type, string_adaptor> >("hc_elementcreatenewattribute::test", &hc_elementcreatenewattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetattributenode<string_type, string_adaptor> >("hc_elementgetattributenode::test", &hc_elementgetattributenode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetattributenodenull<string_type, string_adaptor> >("hc_elementgetattributenodenull::test", &hc_elementgetattributenodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetelementempty<string_type, string_adaptor> >("hc_elementgetelementempty::test", &hc_elementgetelementempty<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetelementsbytagname<string_type, string_adaptor> >("hc_elementgetelementsbytagname::test", &hc_elementgetelementsbytagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetelementsbytagnameaccessnodelist<string_type, string_adaptor> >("hc_elementgetelementsbytagnameaccessnodelist::test", &hc_elementgetelementsbytagnameaccessnodelist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetelementsbytagnamenomatch<string_type, string_adaptor> >("hc_elementgetelementsbytagnamenomatch::test", &hc_elementgetelementsbytagnamenomatch<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgetelementsbytagnamespecialvalue<string_type, string_adaptor> >("hc_elementgetelementsbytagnamespecialvalue::test", &hc_elementgetelementsbytagnamespecialvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementgettagname<string_type, string_adaptor> >("hc_elementgettagname::test", &hc_elementgettagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementinuseattributeerr<string_type, string_adaptor> >("hc_elementinuseattributeerr::test", &hc_elementinuseattributeerr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementinvalidcharacterexception<string_type, string_adaptor> >("hc_elementinvalidcharacterexception::test", &hc_elementinvalidcharacterexception<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementinvalidcharacterexception1<string_type, string_adaptor> >("hc_elementinvalidcharacterexception1::test", &hc_elementinvalidcharacterexception1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementnormalize<string_type, string_adaptor> >("hc_elementnormalize::test", &hc_elementnormalize<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementnormalize2<string_type, string_adaptor> >("hc_elementnormalize2::test", &hc_elementnormalize2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementnotfounderr<string_type, string_adaptor> >("hc_elementnotfounderr::test", &hc_elementnotfounderr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementremoveattribute<string_type, string_adaptor> >("hc_elementremoveattribute::test", &hc_elementremoveattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementremoveattributeaftercreate<string_type, string_adaptor> >("hc_elementremoveattributeaftercreate::test", &hc_elementremoveattributeaftercreate<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementremoveattributenode<string_type, string_adaptor> >("hc_elementremoveattributenode::test", &hc_elementremoveattributenode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementreplaceattributewithself<string_type, string_adaptor> >("hc_elementreplaceattributewithself::test", &hc_elementreplaceattributewithself<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementreplaceexistingattribute<string_type, string_adaptor> >("hc_elementreplaceexistingattribute::test", &hc_elementreplaceexistingattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementreplaceexistingattributegevalue<string_type, string_adaptor> >("hc_elementreplaceexistingattributegevalue::test", &hc_elementreplaceexistingattributegevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementretrieveallattributes<string_type, string_adaptor> >("hc_elementretrieveallattributes::test", &hc_elementretrieveallattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementretrieveattrvalue<string_type, string_adaptor> >("hc_elementretrieveattrvalue::test", &hc_elementretrieveattrvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementretrievetagname<string_type, string_adaptor> >("hc_elementretrievetagname::test", &hc_elementretrievetagname<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementsetattributenodenull<string_type, string_adaptor> >("hc_elementsetattributenodenull::test", &hc_elementsetattributenodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_elementwrongdocumenterr<string_type, string_adaptor> >("hc_elementwrongdocumenterr::test", &hc_elementwrongdocumenterr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_entitiesremovenameditem1<string_type, string_adaptor> >("hc_entitiesremovenameditem1::test", &hc_entitiesremovenameditem1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_entitiessetnameditem1<string_type, string_adaptor> >("hc_entitiessetnameditem1::test", &hc_entitiessetnameditem1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapchildnoderange<string_type, string_adaptor> >("hc_namednodemapchildnoderange::test", &hc_namednodemapchildnoderange<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapgetnameditem<string_type, string_adaptor> >("hc_namednodemapgetnameditem::test", &hc_namednodemapgetnameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapinuseattributeerr<string_type, string_adaptor> >("hc_namednodemapinuseattributeerr::test", &hc_namednodemapinuseattributeerr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapnotfounderr<string_type, string_adaptor> >("hc_namednodemapnotfounderr::test", &hc_namednodemapnotfounderr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapnumberofnodes<string_type, string_adaptor> >("hc_namednodemapnumberofnodes::test", &hc_namednodemapnumberofnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapremovenameditem<string_type, string_adaptor> >("hc_namednodemapremovenameditem::test", &hc_namednodemapremovenameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapreturnattrnode<string_type, string_adaptor> >("hc_namednodemapreturnattrnode::test", &hc_namednodemapreturnattrnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapreturnfirstitem<string_type, string_adaptor> >("hc_namednodemapreturnfirstitem::test", &hc_namednodemapreturnfirstitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapreturnlastitem<string_type, string_adaptor> >("hc_namednodemapreturnlastitem::test", &hc_namednodemapreturnlastitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapreturnnull<string_type, string_adaptor> >("hc_namednodemapreturnnull::test", &hc_namednodemapreturnnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapsetnameditem<string_type, string_adaptor> >("hc_namednodemapsetnameditem::test", &hc_namednodemapsetnameditem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapsetnameditemreturnvalue<string_type, string_adaptor> >("hc_namednodemapsetnameditemreturnvalue::test", &hc_namednodemapsetnameditemreturnvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapsetnameditemthatexists<string_type, string_adaptor> >("hc_namednodemapsetnameditemthatexists::test", &hc_namednodemapsetnameditemthatexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapsetnameditemwithnewvalue<string_type, string_adaptor> >("hc_namednodemapsetnameditemwithnewvalue::test", &hc_namednodemapsetnameditemwithnewvalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_namednodemapwrongdocumenterr<string_type, string_adaptor> >("hc_namednodemapwrongdocumenterr::test", &hc_namednodemapwrongdocumenterr<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchild<string_type, string_adaptor> >("hc_nodeappendchild::test", &hc_nodeappendchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchildchildexists<string_type, string_adaptor> >("hc_nodeappendchildchildexists::test", &hc_nodeappendchildchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchilddocfragment<string_type, string_adaptor> >("hc_nodeappendchilddocfragment::test", &hc_nodeappendchilddocfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchildgetnodename<string_type, string_adaptor> >("hc_nodeappendchildgetnodename::test", &hc_nodeappendchildgetnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchildinvalidnodetype<string_type, string_adaptor> >("hc_nodeappendchildinvalidnodetype::test", &hc_nodeappendchildinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchildnewchilddiffdocument<string_type, string_adaptor> >("hc_nodeappendchildnewchilddiffdocument::test", &hc_nodeappendchildnewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeappendchildnodeancestor<string_type, string_adaptor> >("hc_nodeappendchildnodeancestor::test", &hc_nodeappendchildnodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeattributenodeattribute<string_type, string_adaptor> >("hc_nodeattributenodeattribute::test", &hc_nodeattributenodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeattributenodename<string_type, string_adaptor> >("hc_nodeattributenodename::test", &hc_nodeattributenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeattributenodetype<string_type, string_adaptor> >("hc_nodeattributenodetype::test", &hc_nodeattributenodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeattributenodevalue<string_type, string_adaptor> >("hc_nodeattributenodevalue::test", &hc_nodeattributenodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodechildnodes<string_type, string_adaptor> >("hc_nodechildnodes::test", &hc_nodechildnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodechildnodesappendchild<string_type, string_adaptor> >("hc_nodechildnodesappendchild::test", &hc_nodechildnodesappendchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodechildnodesempty<string_type, string_adaptor> >("hc_nodechildnodesempty::test", &hc_nodechildnodesempty<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodecloneattributescopied<string_type, string_adaptor> >("hc_nodecloneattributescopied::test", &hc_nodecloneattributescopied<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeclonefalsenocopytext<string_type, string_adaptor> >("hc_nodeclonefalsenocopytext::test", &hc_nodeclonefalsenocopytext<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeclonegetparentnull<string_type, string_adaptor> >("hc_nodeclonegetparentnull::test", &hc_nodeclonegetparentnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeclonenodefalse<string_type, string_adaptor> >("hc_nodeclonenodefalse::test", &hc_nodeclonenodefalse<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeclonenodetrue<string_type, string_adaptor> >("hc_nodeclonenodetrue::test", &hc_nodeclonenodetrue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeclonetruecopytext<string_type, string_adaptor> >("hc_nodeclonetruecopytext::test", &hc_nodeclonetruecopytext<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodecommentnodeattributes<string_type, string_adaptor> >("hc_nodecommentnodeattributes::test", &hc_nodecommentnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodecommentnodename<string_type, string_adaptor> >("hc_nodecommentnodename::test", &hc_nodecommentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodecommentnodetype<string_type, string_adaptor> >("hc_nodecommentnodetype::test", &hc_nodecommentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodecommentnodevalue<string_type, string_adaptor> >("hc_nodecommentnodevalue::test", &hc_nodecommentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentfragmentnodename<string_type, string_adaptor> >("hc_nodedocumentfragmentnodename::test", &hc_nodedocumentfragmentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentfragmentnodetype<string_type, string_adaptor> >("hc_nodedocumentfragmentnodetype::test", &hc_nodedocumentfragmentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentfragmentnodevalue<string_type, string_adaptor> >("hc_nodedocumentfragmentnodevalue::test", &hc_nodedocumentfragmentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentnodeattribute<string_type, string_adaptor> >("hc_nodedocumentnodeattribute::test", &hc_nodedocumentnodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentnodename<string_type, string_adaptor> >("hc_nodedocumentnodename::test", &hc_nodedocumentnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentnodetype<string_type, string_adaptor> >("hc_nodedocumentnodetype::test", &hc_nodedocumentnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodedocumentnodevalue<string_type, string_adaptor> >("hc_nodedocumentnodevalue::test", &hc_nodedocumentnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeelementnodeattributes<string_type, string_adaptor> >("hc_nodeelementnodeattributes::test", &hc_nodeelementnodeattributes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeelementnodename<string_type, string_adaptor> >("hc_nodeelementnodename::test", &hc_nodeelementnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeelementnodetype<string_type, string_adaptor> >("hc_nodeelementnodetype::test", &hc_nodeelementnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeelementnodevalue<string_type, string_adaptor> >("hc_nodeelementnodevalue::test", &hc_nodeelementnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetfirstchild<string_type, string_adaptor> >("hc_nodegetfirstchild::test", &hc_nodegetfirstchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetfirstchildnull<string_type, string_adaptor> >("hc_nodegetfirstchildnull::test", &hc_nodegetfirstchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetlastchild<string_type, string_adaptor> >("hc_nodegetlastchild::test", &hc_nodegetlastchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetlastchildnull<string_type, string_adaptor> >("hc_nodegetlastchildnull::test", &hc_nodegetlastchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetnextsibling<string_type, string_adaptor> >("hc_nodegetnextsibling::test", &hc_nodegetnextsibling<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetnextsiblingnull<string_type, string_adaptor> >("hc_nodegetnextsiblingnull::test", &hc_nodegetnextsiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetownerdocument<string_type, string_adaptor> >("hc_nodegetownerdocument::test", &hc_nodegetownerdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetownerdocumentnull<string_type, string_adaptor> >("hc_nodegetownerdocumentnull::test", &hc_nodegetownerdocumentnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetprevioussibling<string_type, string_adaptor> >("hc_nodegetprevioussibling::test", &hc_nodegetprevioussibling<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodegetprevioussiblingnull<string_type, string_adaptor> >("hc_nodegetprevioussiblingnull::test", &hc_nodegetprevioussiblingnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodehaschildnodes<string_type, string_adaptor> >("hc_nodehaschildnodes::test", &hc_nodehaschildnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodehaschildnodesfalse<string_type, string_adaptor> >("hc_nodehaschildnodesfalse::test", &hc_nodehaschildnodesfalse<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbefore<string_type, string_adaptor> >("hc_nodeinsertbefore::test", &hc_nodeinsertbefore<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforedocfragment<string_type, string_adaptor> >("hc_nodeinsertbeforedocfragment::test", &hc_nodeinsertbeforedocfragment<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforeinvalidnodetype<string_type, string_adaptor> >("hc_nodeinsertbeforeinvalidnodetype::test", &hc_nodeinsertbeforeinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforenewchilddiffdocument<string_type, string_adaptor> >("hc_nodeinsertbeforenewchilddiffdocument::test", &hc_nodeinsertbeforenewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforenewchildexists<string_type, string_adaptor> >("hc_nodeinsertbeforenewchildexists::test", &hc_nodeinsertbeforenewchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforenodeancestor<string_type, string_adaptor> >("hc_nodeinsertbeforenodeancestor::test", &hc_nodeinsertbeforenodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforenodename<string_type, string_adaptor> >("hc_nodeinsertbeforenodename::test", &hc_nodeinsertbeforenodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforerefchildnonexistent<string_type, string_adaptor> >("hc_nodeinsertbeforerefchildnonexistent::test", &hc_nodeinsertbeforerefchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeinsertbeforerefchildnull<string_type, string_adaptor> >("hc_nodeinsertbeforerefchildnull::test", &hc_nodeinsertbeforerefchildnull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistindexequalzero<string_type, string_adaptor> >("hc_nodelistindexequalzero::test", &hc_nodelistindexequalzero<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistindexgetlength<string_type, string_adaptor> >("hc_nodelistindexgetlength::test", &hc_nodelistindexgetlength<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistindexgetlengthofemptylist<string_type, string_adaptor> >("hc_nodelistindexgetlengthofemptylist::test", &hc_nodelistindexgetlengthofemptylist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistindexnotzero<string_type, string_adaptor> >("hc_nodelistindexnotzero::test", &hc_nodelistindexnotzero<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistreturnfirstitem<string_type, string_adaptor> >("hc_nodelistreturnfirstitem::test", &hc_nodelistreturnfirstitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelistreturnlastitem<string_type, string_adaptor> >("hc_nodelistreturnlastitem::test", &hc_nodelistreturnlastitem<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodelisttraverselist<string_type, string_adaptor> >("hc_nodelisttraverselist::test", &hc_nodelisttraverselist<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeparentnode<string_type, string_adaptor> >("hc_nodeparentnode::test", &hc_nodeparentnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodeparentnodenull<string_type, string_adaptor> >("hc_nodeparentnodenull::test", &hc_nodeparentnodenull<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_noderemovechild<string_type, string_adaptor> >("hc_noderemovechild::test", &hc_noderemovechild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_noderemovechildgetnodename<string_type, string_adaptor> >("hc_noderemovechildgetnodename::test", &hc_noderemovechildgetnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_noderemovechildnode<string_type, string_adaptor> >("hc_noderemovechildnode::test", &hc_noderemovechildnode<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_noderemovechildoldchildnonexistent<string_type, string_adaptor> >("hc_noderemovechildoldchildnonexistent::test", &hc_noderemovechildoldchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechild<string_type, string_adaptor> >("hc_nodereplacechild::test", &hc_nodereplacechild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildinvalidnodetype<string_type, string_adaptor> >("hc_nodereplacechildinvalidnodetype::test", &hc_nodereplacechildinvalidnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildnewchilddiffdocument<string_type, string_adaptor> >("hc_nodereplacechildnewchilddiffdocument::test", &hc_nodereplacechildnewchilddiffdocument<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildnewchildexists<string_type, string_adaptor> >("hc_nodereplacechildnewchildexists::test", &hc_nodereplacechildnewchildexists<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildnodeancestor<string_type, string_adaptor> >("hc_nodereplacechildnodeancestor::test", &hc_nodereplacechildnodeancestor<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildnodename<string_type, string_adaptor> >("hc_nodereplacechildnodename::test", &hc_nodereplacechildnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodereplacechildoldchildnonexistent<string_type, string_adaptor> >("hc_nodereplacechildoldchildnonexistent::test", &hc_nodereplacechildoldchildnonexistent<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodetextnodeattribute<string_type, string_adaptor> >("hc_nodetextnodeattribute::test", &hc_nodetextnodeattribute<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodetextnodename<string_type, string_adaptor> >("hc_nodetextnodename::test", &hc_nodetextnodename<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodetextnodetype<string_type, string_adaptor> >("hc_nodetextnodetype::test", &hc_nodetextnodetype<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodetextnodevalue<string_type, string_adaptor> >("hc_nodetextnodevalue::test", &hc_nodetextnodevalue<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue01<string_type, string_adaptor> >("hc_nodevalue01::test", &hc_nodevalue01<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue02<string_type, string_adaptor> >("hc_nodevalue02::test", &hc_nodevalue02<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue03<string_type, string_adaptor> >("hc_nodevalue03::test", &hc_nodevalue03<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue04<string_type, string_adaptor> >("hc_nodevalue04::test", &hc_nodevalue04<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue05<string_type, string_adaptor> >("hc_nodevalue05::test", &hc_nodevalue05<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue06<string_type, string_adaptor> >("hc_nodevalue06::test", &hc_nodevalue06<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue07<string_type, string_adaptor> >("hc_nodevalue07::test", &hc_nodevalue07<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_nodevalue08<string_type, string_adaptor> >("hc_nodevalue08::test", &hc_nodevalue08<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_notationsremovenameditem1<string_type, string_adaptor> >("hc_notationsremovenameditem1::test", &hc_notationsremovenameditem1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_notationssetnameditem1<string_type, string_adaptor> >("hc_notationssetnameditem1::test", &hc_notationssetnameditem1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textindexsizeerrnegativeoffset<string_type, string_adaptor> >("hc_textindexsizeerrnegativeoffset::test", &hc_textindexsizeerrnegativeoffset<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textindexsizeerroffsetoutofbounds<string_type, string_adaptor> >("hc_textindexsizeerroffsetoutofbounds::test", &hc_textindexsizeerroffsetoutofbounds<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textparseintolistofelements<string_type, string_adaptor> >("hc_textparseintolistofelements::test", &hc_textparseintolistofelements<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textsplittextfour<string_type, string_adaptor> >("hc_textsplittextfour::test", &hc_textsplittextfour<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textsplittextone<string_type, string_adaptor> >("hc_textsplittextone::test", &hc_textsplittextone<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textsplittextthree<string_type, string_adaptor> >("hc_textsplittextthree::test", &hc_textsplittextthree<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textsplittexttwo<string_type, string_adaptor> >("hc_textsplittexttwo::test", &hc_textsplittexttwo<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_textwithnomarkup<string_type, string_adaptor> >("hc_textwithnomarkup::test", &hc_textwithnomarkup<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild1<string_type, string_adaptor> >("hc_attrappendchild1::test", &hc_attrappendchild1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild2<string_type, string_adaptor> >("hc_attrappendchild2::test", &hc_attrappendchild2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild3<string_type, string_adaptor> >("hc_attrappendchild3::test", &hc_attrappendchild3<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild4<string_type, string_adaptor> >("hc_attrappendchild4::test", &hc_attrappendchild4<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild5<string_type, string_adaptor> >("hc_attrappendchild5::test", &hc_attrappendchild5<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrappendchild6<string_type, string_adaptor> >("hc_attrappendchild6::test", &hc_attrappendchild6<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrchildnodes1<string_type, string_adaptor> >("hc_attrchildnodes1::test", &hc_attrchildnodes1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrchildnodes2<string_type, string_adaptor> >("hc_attrchildnodes2::test", &hc_attrchildnodes2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrclonenode1<string_type, string_adaptor> >("hc_attrclonenode1::test", &hc_attrclonenode1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrfirstchild<string_type, string_adaptor> >("hc_attrfirstchild::test", &hc_attrfirstchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrgetvalue1<string_type, string_adaptor> >("hc_attrgetvalue1::test", &hc_attrgetvalue1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrgetvalue2<string_type, string_adaptor> >("hc_attrgetvalue2::test", &hc_attrgetvalue2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrhaschildnodes<string_type, string_adaptor> >("hc_attrhaschildnodes::test", &hc_attrhaschildnodes<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore1<string_type, string_adaptor> >("hc_attrinsertbefore1::test", &hc_attrinsertbefore1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore2<string_type, string_adaptor> >("hc_attrinsertbefore2::test", &hc_attrinsertbefore2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore3<string_type, string_adaptor> >("hc_attrinsertbefore3::test", &hc_attrinsertbefore3<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore4<string_type, string_adaptor> >("hc_attrinsertbefore4::test", &hc_attrinsertbefore4<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore5<string_type, string_adaptor> >("hc_attrinsertbefore5::test", &hc_attrinsertbefore5<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore6<string_type, string_adaptor> >("hc_attrinsertbefore6::test", &hc_attrinsertbefore6<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrinsertbefore7<string_type, string_adaptor> >("hc_attrinsertbefore7::test", &hc_attrinsertbefore7<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrlastchild<string_type, string_adaptor> >("hc_attrlastchild::test", &hc_attrlastchild<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrnormalize<string_type, string_adaptor> >("hc_attrnormalize::test", &hc_attrnormalize<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrremovechild1<string_type, string_adaptor> >("hc_attrremovechild1::test", &hc_attrremovechild1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrremovechild2<string_type, string_adaptor> >("hc_attrremovechild2::test", &hc_attrremovechild2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrreplacechild1<string_type, string_adaptor> >("hc_attrreplacechild1::test", &hc_attrreplacechild1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrreplacechild2<string_type, string_adaptor> >("hc_attrreplacechild2::test", &hc_attrreplacechild2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrsetvalue1<string_type, string_adaptor> >("hc_attrsetvalue1::test", &hc_attrsetvalue1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<hc_attrsetvalue2<string_type, string_adaptor> >("hc_attrsetvalue2::test", &hc_attrsetvalue2<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrremovechild1<string_type, string_adaptor> >("attrremovechild1::test", &attrremovechild1<string_type, string_adaptor>::runTest));
  suiteOfTests->addTest(new TestCaller<attrreplacechild1<string_type, string_adaptor> >("attrreplacechild1::test", &attrreplacechild1<string_type, string_adaptor>::runTest));

  return suiteOfTests;
}

#endif
