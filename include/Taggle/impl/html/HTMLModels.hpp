#ifndef ARABICA_SAX_TAGGLE_HTML_MODELS_HPP
#define ARABICA_SAX_TAGGLE_HTML_MODELS_HPP

namespace Arabica
{

namespace SAX
{

/**
This interface contains generated constants representing HTML content
models.  Logically, it is part of HTMLSchema, but it is more
convenient to generate the constants into a separate interface.

Based on code from John Cowan's super TagSoup package
*/
class HTMLModels 
{
protected:
	// Start of model definitions
	static const int M_AREA = 1 << 1;
	static const int M_BLOCK = 1 << 2;
	static const int M_BLOCKINLINE = 1 << 3;
	static const int M_BODY = 1 << 4;
	static const int M_CELL = 1 << 5;
	static const int M_COL = 1 << 6;
	static const int M_DEF = 1 << 7;
	static const int M_FORM = 1 << 8;
	static const int M_FRAME = 1 << 9;
	static const int M_HEAD = 1 << 10;
	static const int M_HTML = 1 << 11;
	static const int M_INLINE = 1 << 12;
	static const int M_LEGEND = 1 << 13;
	static const int M_LI = 1 << 14;
	static const int M_NOLINK = 1 << 15;
	static const int M_OPTION = 1 << 16;
	static const int M_OPTIONS = 1 << 17;
	static const int M_P = 1 << 18;
	static const int M_PARAM = 1 << 19;
	static const int M_TABLE = 1 << 20;
	static const int M_TABULAR = 1 << 21;
	static const int M_TR = 1 << 22;
}; // namespace HTMLModels

} // namespace SAX

} // namespace Arabica
#endif

