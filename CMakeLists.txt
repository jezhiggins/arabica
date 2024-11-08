#
# CMakeLists.txt file for arabica xml
#

cmake_minimum_required(VERSION 3.5)

project(arabica)

# Enable C++14 support
set(CMAKE_CXX_STANDARD 14)

set(LIB_NAME arabica)

set(ARABICA_MAJOR_VERSION 2024)
set(ARABICA_MINOR_VERSION September)

#
# Packaging details
#
set(CPACK_PACKAGE_NAME "libarabica")
set(CPACK_PACKAGE_VENDOR "Jez Higgins <jez@jezuk.co.uk>")
set(CPACK_PACKAGE_CONTACT "Jez Higgins <jez@jezuk.co.uk>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Arabica is an XML and HTML processing toolkit, providing SAX2, DOM, XPath, and XSLT implementations, written in Standard C++")
set(CPACK_PACKAGE_VERSION_MAJOR ${ARABICA_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${ARABICA_MINOR_VERSION})

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libexpat1")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/jezhiggins/arabica")

set(CPACK_RPM_PACKAGE_LICENSE "BSD 3-clause")
set(CPACK_RPM_PACKAGE_URL "https://github.com/jezhiggins/arabica")
set(CPACK_RPM_PACKAGE_REQUIRES "expat")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")

#set(CPACK_GENERATOR "TGZ;DEB;RPM")
set(CPACK_GENERATOR "TGZ;DEB;")

#
# Build as shared library
#
option(BUILD_SHARED_LIBS "Build as shared libaries" OFF)

#
# Enable/Disable example build
#
option(BUILD_ARABICA_EXAMPLES "Build all arabica examples" ON)


option(BUILD_ARABICA_TESTS "Build tests" OFF)

#
# Enable/Disable Boost
#
option(BUILD_WITH_BOOST "Build with Boost" OFF)

#
# Set variables for configuration
#
if(WIN32)
  set(ARABICA_NO_CODECVT_SPECIALISATIONS TRUE)
  set(USE_WINSOCK TRUE)
  set(ARABICA_WINDOWS TRUE)
  if(MSVC_VERSION LESS 1300)
    set(ARABICA_VS6_WORKAROUND TRUE)
  endif()

  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if(BUILD_WITH_BOOST)
  set(ARABICA_HAVE_BOOST TRUE)
endif()

#
# Enable target folders in Visual Studio and other IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#
# Set the used xml backend
# options: USE_MSXML, USE_EXPAT, USE_LIBXML2, USE_XERCES
# default for windows: MSXML
# default for linux:   EXPAT
if(NOT ARABICA_XML_BACKEND)
  if(WIN32)
    set(ARABICA_XML_BACKEND USE_MSXML)
  elseif(APPLE)
    set(ARABICA_XML_BACKEND USE_LIBXML2)
  else()
    set(ARABICA_XML_BACKEND USE_EXPAT)
  endif()
endif()

#
# Find boost
if(BUILD_WITH_BOOST)
  if(NOT TARGET boost)
    ## BOOST_ROOT has to be set correctly
    if(NOT DEFINED BOOST_ROOT)
      set(BOOST_ROOT "../boost") # reasonable default: boost is in a parallel directory
    endif()
    find_package(Boost REQUIRED)
  endif()
endif()

#
# Find expat
if(ARABICA_XML_BACKEND STREQUAL USE_EXPAT)
  set(ARABICA_USE_EXPAT TRUE)
  if(NOT TARGET expat)
    find_package(EXPAT REQUIRED)
    set(ADDITIONAL_INC ${EXPAT_INCLUDE_DIRS})
    set(ADDITIONAL_LIB ${EXPAT_LIBRARY})
  else()
    # set externally
    set(ADDITIONAL_INC ${EXPAT_INCLUDE_DIRS})
    set(ADDITIONAL_LIB ${EXPAT_LIBRARIES})
  endif()
endif()

#
# find libxml2: LIBXML2_INCLUDE_DIR LIBXML2_LIBRARIES
if(ARABICA_XML_BACKEND STREQUAL USE_LIBXML2)
  set(ARABICA_USE_LIBXML2 TRUE)
  find_package(LibXml2 REQUIRED)
  set(ADDITIONAL_INC ${LIBXML2_INCLUDE_DIRS})
  set(ADDITIONAL_LIB ${LIBXML2_LIBRARIES})
endif()

#
# find Xerces: XERCES_INCLUDE_DIR XERCES_LIBRARIES
if(ARABICA_XML_BACKEND STREQUAL USE_XERCES)
  set(ARABICA_USE_XERCES TRUE)
  find_package(XercesC REQUIRED)
  set(ADDITIONAL_INC ${XercesC_INCLUDE_DIRS})
  set(ADDITIONAL_LIB ${XercesC_LIBRARIES})
endif()

#
# platform check
#
# Check for 64 bit build
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(BUILD_X64 TRUE)
  set(BUILD_X86 FALSE)
else()
  set(BUILD_X64 FALSE)
  set(BUILD_X86 TRUE)
endif()


if(BUILD_ARABICA_EXAMPLES)
  message(STATUS "Building ${LIB_NAME} with ${ARABICA_XML_BACKEND} compile flag with examples")
else()
  message(STATUS "Building ${LIB_NAME} with ${ARABICA_XML_BACKEND} compile flag library only")
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/SAX/ArabicaConfig.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/SAX/ArabicaConfig.hpp)

set(GENERATED_HEADER_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/include/SAX/ArabicaConfig.hpp
)
source_group("Generated Header Files" FILES ${GENERATED_HEADER_FILES})

set(PUBLIC_HEADER_FILES
  include/SAX/AttributeList.hpp
  include/SAX/Attributes.hpp
  include/SAX/ContentHandler.hpp
  include/SAX/DocumentHandler.hpp
  include/SAX/DTDHandler.hpp
  include/SAX/EntityResolver.hpp
  include/SAX/ErrorHandler.hpp
  include/SAX/HandlerBase.hpp
  include/SAX/InputSource.hpp
  include/SAX/IStreamHandle.hpp
  include/SAX/Locator.hpp
  include/SAX/Parser.hpp
  include/SAX/ParserConfig.hpp
  include/SAX/SAXException.hpp
  include/SAX/saxfwd.hpp
  include/SAX/SAXNotRecognizedException.hpp
  include/SAX/SAXNotSupportedException.hpp
  include/SAX/SAXParseException.hpp
  include/SAX/XMLFilter.hpp
  include/SAX/XMLReader.hpp
  include/SAX/ext/Attributes2.hpp
  include/SAX/ext/DeclHandler.hpp
  include/SAX/ext/DefaultHandler2.hpp
  include/SAX/ext/LexicalHandler.hpp
  include/SAX/ext/Locator2.hpp
  include/SAX/ext/ProgressiveParser.hpp
  include/SAX/filter/NamespaceTracker.hpp
  include/SAX/filter/TextCoalescer.hpp
  include/SAX/filter/TextOnly.hpp
  include/SAX/filter/Writer.hpp
  include/SAX/filter/XMLBaseTracker.hpp
  include/SAX/helpers/AttributeDefaults.hpp
  include/SAX/helpers/AttributeListImpl.hpp
  include/SAX/helpers/AttributesImpl.hpp
  include/SAX/helpers/AttributeTypes.hpp
  include/SAX/helpers/CatchErrorHandler.hpp
  include/SAX/helpers/DefaultHandler.hpp
  include/SAX/helpers/FeatureNames.hpp
  include/SAX/helpers/InputSourceResolver.hpp
  include/SAX/helpers/LocatorImpl.hpp
  include/SAX/helpers/NamespaceSupport.hpp
  include/SAX/helpers/XMLBaseSupport.hpp
  include/SAX/helpers/XMLFilterImpl.hpp
  include/SAX/parsers/saxgarden.hpp
  include/SAX/wrappers/saxexpat.hpp
  include/SAX/wrappers/saxlibxml2.hpp
  include/SAX/wrappers/saxmsxml2.hpp
  include/SAX/wrappers/saxxerces.hpp
  include/DOM/Attr.hpp
  include/DOM/CDATASection.hpp
  include/DOM/CharacterData.hpp
  include/DOM/Comment.hpp
  include/DOM/Document.hpp
  include/DOM/DocumentFragment.hpp
  include/DOM/DocumentType.hpp
  include/DOM/DOMException.hpp
  include/DOM/DOMImplementation.hpp
  include/DOM/Element.hpp
  include/DOM/Entity.hpp
  include/DOM/EntityReference.hpp
  include/DOM/NamedNodeMap.hpp
  include/DOM/Node.hpp
  include/DOM/NodeList.hpp
  include/DOM/Notation.hpp
  include/DOM/ProcessingInstruction.hpp
  include/DOM/Proxy.hpp
  include/DOM/Text.hpp
  include/DOM/DualMode/DualMode.hpp
  include/DOM/Events/DocumentEvent.hpp
  include/DOM/Events/Event.hpp
  include/DOM/Events/EventException.hpp
  include/DOM/Events/EventListener.hpp
  include/DOM/Events/EventTarget.hpp
  include/DOM/Events/MutationEvent.hpp
  include/DOM/SAX2DOM/DocumentTypeImpl.hpp
  include/DOM/SAX2DOM/SAX2DOM.hpp
  include/DOM/Simple/AttrImpl.hpp
  include/DOM/Simple/AttrMap.hpp
  include/DOM/Simple/AttrNSImpl.hpp
  include/DOM/Simple/CDATASectionImpl.hpp
  include/DOM/Simple/CharacterDataImpl.hpp
  include/DOM/Simple/CommentImpl.hpp
  include/DOM/Simple/DocumentFragmentImpl.hpp
  include/DOM/Simple/DocumentImpl.hpp
  include/DOM/Simple/DocumentTypeImpl.hpp
  include/DOM/Simple/DOMImplementation.hpp
  include/DOM/Simple/ElementByTagImpl.hpp
  include/DOM/Simple/ElementImpl.hpp
  include/DOM/Simple/ElementNSImpl.hpp
  include/DOM/Simple/EntityImpl.hpp
  include/DOM/Simple/EntityReferenceImpl.hpp
  include/DOM/Simple/Helpers.hpp
  include/DOM/Simple/NamedNodeMapImpl.hpp
  include/DOM/Simple/NodeImpl.hpp
  include/DOM/Simple/NotationImpl.hpp
  include/DOM/Simple/ProcessingInstructionImpl.hpp
  include/DOM/Simple/TextImpl.hpp
  include/DOM/Traversal/DocumentTraversal.hpp
  include/DOM/Traversal/DocumentTraversalImpl.hpp
  include/DOM/Traversal/NodeFilter.hpp
  include/DOM/Traversal/NodeIterator.hpp
  include/DOM/Traversal/TraversalImpl.hpp
  include/DOM/Traversal/TreeWalker.hpp
  include/DOM/Traversal/TreeWalkerImpl.hpp
  include/DOM/io/Stream.hpp
  include/XPath/XPath.hpp
  include/XPath/impl/xpath_arithmetic.hpp
  include/XPath/impl/xpath_ast.hpp
  include/XPath/impl/xpath_ast_ids.hpp
  include/XPath/impl/xpath_axis_enumerator.hpp
  include/XPath/impl/xpath_compile_context.hpp
  include/XPath/impl/xpath_execution_context.hpp
  include/XPath/impl/xpath_expression.hpp
  include/XPath/impl/xpath_expression_impl.hpp
  include/XPath/impl/xpath_function.hpp
  include/XPath/impl/xpath_function_holder.hpp
  include/XPath/impl/xpath_function_resolver.hpp
  include/XPath/impl/xpath_grammar.hpp
  include/XPath/impl/xpath_logical.hpp
  include/XPath/impl/xpath_match.hpp
  include/XPath/impl/xpath_match_rewrite.hpp
  include/XPath/impl/xpath_namespace_context.hpp
  include/XPath/impl/xpath_namespace_node.hpp
  include/XPath/impl/xpath_node_test.hpp
  include/XPath/impl/xpath_object.hpp
  include/XPath/impl/xpath_parser.hpp
  include/XPath/impl/xpath_relational.hpp
  include/XPath/impl/xpath_resolver_holder.hpp
  include/XPath/impl/xpath_step.hpp
  include/XPath/impl/xpath_union.hpp
  include/XPath/impl/xpath_value.hpp
  include/XPath/impl/xpath_variable.hpp
  include/XPath/impl/xpath_variable_resolver.hpp
  include/Arabica/getparam.hpp
  include/Arabica/StringAdaptor.hpp
  include/Arabica/stringadaptortag.hpp
  include/XML/escaper.hpp
  include/XML/QName.hpp
  include/XML/strings.hpp
  include/XML/XMLCharacterClasses.hpp
  include/io/convert_adaptor.hpp
  include/io/convertstream.hpp
  include/io/socket_stream.hpp
  include/io/uri.hpp
  include/convert/base64codecvt.hpp
  include/convert/impl/codecvt_specialisations.hpp
  include/convert/impl/iso88591_utf8.hpp
  include/convert/iso88591utf8codecvt.hpp
  include/convert/rot13codecvt.hpp
  include/convert/impl/ucs2_utf16.hpp
  include/convert/impl/ucs2_utf8.hpp
  include/convert/ucs2utf8codecvt.hpp
  include/convert/utf16beucs2codecvt.hpp
  include/convert/utf16leucs2codecvt.hpp
  include/convert/utf16utf8codecvt.hpp
  include/convert/utf8iso88591codecvt.hpp
  include/convert/utf8ucs2codecvt.hpp
  include/text/normalize_whitespace.hpp
  include/text/UnicodeCharacters.hpp
  include/Taggle/impl/Element.hpp
  include/Taggle/impl/ElementType.hpp
  include/Taggle/impl/html/HTMLModels.hpp
  include/Taggle/impl/html/HTMLScanner.hpp
  include/Taggle/impl/html/HTMLSchema.hpp
  include/Taggle/impl/Parser.hpp
  include/Taggle/impl/ScanHandler.hpp
  include/Taggle/impl/Scanner.hpp
  include/Taggle/impl/Schema.hpp
  include/Taggle/impl/SchemaImpl.hpp
  include/Taggle/Taggle.hpp
  include/XSLT/XSLT.hpp
  include/XSLT/impl/xslt_apply_imports.hpp
  include/XSLT/impl/xslt_apply_templates.hpp
  include/XSLT/impl/xslt_attribute.hpp
  include/XSLT/impl/xslt_call_template.hpp
  include/XSLT/impl/xslt_choose.hpp
  include/XSLT/impl/xslt_comment.hpp
  include/XSLT/impl/xslt_compilation_context.hpp
  include/XSLT/impl/xslt_compiled_stylesheet.hpp
  include/XSLT/impl/xslt_copy.hpp
  include/XSLT/impl/xslt_element.hpp
  include/XSLT/impl/xslt_execution_context.hpp
  include/XSLT/impl/xslt_for_each.hpp
  include/XSLT/impl/xslt_functions.hpp
  include/XSLT/impl/xslt_if.hpp
  include/XSLT/impl/xslt_inline_element.hpp
  include/XSLT/impl/xslt_item.hpp
  include/XSLT/impl/xslt_key.hpp
  include/XSLT/impl/xslt_message.hpp
  include/XSLT/impl/xslt_namespace_stack.hpp
  include/XSLT/impl/xslt_output.hpp
  include/XSLT/impl/xslt_param.hpp
  include/XSLT/impl/xslt_precedence.hpp
  include/XSLT/impl/xslt_processing_instruction.hpp
  include/XSLT/impl/xslt_qname.hpp
  include/XSLT/impl/xslt_sink.hpp
  include/XSLT/impl/xslt_sort.hpp
  include/XSLT/impl/xslt_stylesheet.hpp
  include/XSLT/impl/xslt_stylesheet_compiler.hpp
  include/XSLT/impl/xslt_stylesheet_parser.hpp
  include/XSLT/impl/xslt_template.hpp
  include/XSLT/impl/xslt_text.hpp
  include/XSLT/impl/xslt_top_level_param.hpp
  include/XSLT/impl/xslt_value_of.hpp
  include/XSLT/impl/xslt_variable.hpp
  include/XSLT/impl/xslt_variable_impl.hpp
  include/XSLT/impl/xslt_variable_stack.hpp
  include/XSLT/impl/xslt_with_param.hpp
  include/XSLT/impl/handler/xslt_apply_imports_handler.hpp
  include/XSLT/impl/handler/xslt_apply_templates_handler.hpp
  include/XSLT/impl/handler/xslt_attribute_handler.hpp
  include/XSLT/impl/handler/xslt_call_template_handler.hpp
  include/XSLT/impl/handler/xslt_choose_handler.hpp
  include/XSLT/impl/handler/xslt_comment_handler.hpp
  include/XSLT/impl/handler/xslt_constants.hpp
  include/XSLT/impl/handler/xslt_copy_handler.hpp
  include/XSLT/impl/handler/xslt_create_handler.hpp
  include/XSLT/impl/handler/xslt_element_handler.hpp
  include/XSLT/impl/handler/xslt_for_each_handler.hpp
  include/XSLT/impl/handler/xslt_if_handler.hpp
  include/XSLT/impl/handler/xslt_include_handler.hpp
  include/XSLT/impl/handler/xslt_inline_element_handler.hpp
  include/XSLT/impl/handler/xslt_item_container_handler.hpp
  include/XSLT/impl/handler/xslt_key_handler.hpp
  include/XSLT/impl/handler/xslt_message_handler.hpp
  include/XSLT/impl/handler/xslt_namespace_alias_handler.hpp
  include/XSLT/impl/handler/xslt_output_handler.hpp
  include/XSLT/impl/handler/xslt_processing_instruction_handler.hpp
  include/XSLT/impl/handler/xslt_sort_handler.hpp
  include/XSLT/impl/handler/xslt_template_handler.hpp
  include/XSLT/impl/handler/xslt_text_handler.hpp
  include/XSLT/impl/handler/xslt_value_of_handler.hpp
  include/XSLT/impl/handler/xslt_value_validation.hpp
  include/XSLT/impl/handler/xslt_variable_handler.hpp
  include/XSLT/impl/handler/xslt_with_param_handler.hpp
  )
source_group("Header Files" FILES ${PUBLIC_HEADER_FILES})

set(SOURCE_FILES
  src/arabica.cpp
  src/XML/XMLCharacterClasses.cpp
  src/SAX/helpers/InputSourceResolver.cpp
  src/io/uri.cpp
  src/convert/base64codecvt.cpp
  src/convert/impl/iso88591_utf8.cpp
  src/convert/iso88591utf8codecvt.cpp
  src/convert/rot13codecvt.cpp
  src/convert/impl/ucs2_utf16.cpp
  src/convert/impl/ucs2_utf8.cpp
  src/convert/ucs2utf8codecvt.cpp
  src/convert/utf16beucs2codecvt.cpp
  src/convert/utf16leucs2codecvt.cpp
  src/convert/utf16utf8codecvt.cpp
  src/convert/utf8iso88591codecvt.cpp
  src/convert/utf8ucs2codecvt.cpp
  src/taggle/Schema.cpp
)
source_group("Source Files" FILES ${SOURCE_FILES})


add_library (${LIB_NAME}
  ${GENERATED_HEADER_FILES}
  ${PUBLIC_HEADER_FILES}
  ${SOURCE_FILES}
)
target_compile_definitions(${LIB_NAME} PUBLIC "$<$<CONFIG:Debug>:ARABICA_DEBUG>")
target_compile_definitions(${LIB_NAME} PUBLIC ARABICA_NOT_USE_PRAGMA_LINKER_OPTIONS)
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)
target_include_directories(${LIB_NAME} PUBLIC ${ADDITIONAL_INC} ${Boost_INCLUDE_DIRS})
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
# link backend
target_link_libraries(${LIB_NAME} ${ADDITIONAL_LIB})

# VS2010 bug for 64bit builds
if(MSVC)
  if(BUILD_X64)
    set_property(TARGET ${LIB_NAME}
      APPEND
      PROPERTY STATIC_LIBRARY_FLAGS
      /MACHINE:X64
      )
  endif()
endif()


if(MSVC)
  # link socket library in windows
  target_link_libraries(${LIB_NAME}
    ws2_32.lib
  )
endif()


#
# Add build dependency to boost if boost is part of the same project
if(TARGET boost)
  add_dependencies(${LIB_NAME} boost)
endif()

set_target_properties(${LIB_NAME} PROPERTIES FOLDER "3rdparty/arabica")

#
# Install library
#
install(TARGETS ${LIB_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static
)

install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/SAX/ArabicaConfig.hpp
  DESTINATION include/${PROJECT_NAME}/SAX
)

#
# tests
if(BUILD_ARABICA_TESTS)
  message(STATUS "Building tests with ${ARABICA_XML_BACKEND} compile flag")

  include(CTest)

  set(CPP_UNIT_SOURCES
    tests/CppUnit/TestRunner.hpp
    tests/CppUnit/framework/CppUnitException.h
    tests/CppUnit/framework/estring.h
    tests/CppUnit/framework/Guards.h
    tests/CppUnit/framework/Test.h
    tests/CppUnit/framework/TestCaller.h
    tests/CppUnit/framework/TestCase.h
    tests/CppUnit/framework/TestFailure.h
    tests/CppUnit/framework/TestResult.h
    tests/CppUnit/framework/TestSuite.h
    tests/CppUnit/textui/TextTestResult.h
    tests/CppUnit/textui/TableTestResult.hpp
    tests/CppUnit/textui/XmlTestResult.hpp
    tests/CppUnit/framework/TestCase.cpp
    tests/CppUnit/framework/TestFailure.cpp
    tests/CppUnit/framework/TestResult.cpp
    tests/CppUnit/framework/TestSuite.cpp
    tests/CppUnit/TestRunner.cpp
    tests/CppUnit/textui/TextTestResult.cpp
    tests/CppUnit/textui/TableTestResult.cpp
    tests/CppUnit/textui/XmlTestResult.cpp
  )
  add_library(cppunit STATIC
          ${CPP_UNIT_SOURCES})

  add_executable(test_sax_filter tests/SAX/filter_test.cpp)
  target_link_libraries(test_sax_filter arabica cppunit)
  add_executable(test_sax_filter_wide tests/SAX/filter_test_wide.cpp)
  target_link_libraries(test_sax_filter_wide arabica cppunit)
  add_test(sax_filter test_sax_filter -v)
  add_test(sax_filter_wide test_sax_filter_wide -v)

  set(DOM_TEST_SOURCES
    tests/DOM/dom_test_suite.hpp
    tests/DOM/dom_conf_test.hpp
    tests/DOM/test_Attribute.hpp
    tests/DOM/test_CDATA.hpp
    tests/DOM/test_CharacterData.hpp
    tests/DOM/test_DOMImplementation.hpp
    tests/DOM/test_Document.hpp
    tests/DOM/test_DocumentFragment.hpp
    tests/DOM/test_DocumentType.hpp
    tests/DOM/test_Element.hpp
    tests/DOM/test_NamedNodeMap.hpp
    tests/DOM/test_ProcessingInstruction.hpp
    tests/DOM/test_Siblings.hpp
    tests/DOM/test_Text.hpp
    tests/DOM/test_SAX2DOM.hpp
    tests/DOM/test_TreeWalker.hpp
    tests/DOM/test_Stream.hpp
  )
  add_executable(test_dom tests/DOM/main.cpp ${DOM_TEST_SOURCES})
  include_directories(test_dom tests/DOM)
  target_link_libraries(test_dom arabica cppunit)
  add_executable(test_dom_wide tests/DOM/main_wide.cpp ${DOM_TEST_SOURCES})
  include_directories(test_dom_wide tests/DOM)
  target_link_libraries(test_dom_wide arabica cppunit)
  add_test(dom test_dom -v)
  add_test(dom_wide test_dom_wide -v)

  add_executable(test_taggle tests/Taggle/taggle_test.cpp tests/Taggle/test_Taggle.hpp)
  target_link_libraries(test_taggle arabica cppunit)
  add_test(taggle test_taggle -v)

  set(UTIL_TEST_SOURCES
    tests/Utils/test_base64.hpp
    tests/Utils/test_normalize_whitespace.hpp
    tests/Utils/test_qname.hpp
    tests/Utils/test_uri.hpp
    tests/Utils/test_xml_strings.hpp
    tests/Utils/util_test_suite.hpp
  )
  add_executable(test_util tests/Utils/utils_test.cpp ${UTIL_TEST_SOURCES})
  target_link_libraries(test_util arabica cppunit)
  add_executable(test_util_wide tests/Utils/utils_test_wide.cpp ${UTIL_TEST_SOURCES})
  target_link_libraries(test_util_wide arabica cppunit)
  add_test(util test_util -v)
  add_test(util_wide test_util_wide -v)

  set(XPATH_TEST_SOURCES
    tests/XPath/arithmetic_test.hpp
    tests/XPath/attr_value_test.hpp
    tests/XPath/axis_enumerator_test.hpp
    tests/XPath/execute_test.hpp
    tests/XPath/expression_test.hpp
    tests/XPath/logical_test.hpp
    tests/XPath/match_test.hpp
    tests/XPath/node_test_test.hpp
    tests/XPath/parse_test.hpp
    tests/XPath/relational_test.hpp
    tests/XPath/step_test.hpp
    tests/XPath/text_node_test.hpp
    tests/XPath/value_test.hpp
    tests/XPath/xpath_test_suite.hpp
  )
  add_executable(test_xpath tests/XPath/main.cpp ${XPATH_TEST_SOURCES})
  target_link_libraries(test_xpath arabica cppunit)
  add_executable(test_xpath_wide tests/XPath/main_wide.cpp ${XPATH_TEST_SOURCES})
  target_link_libraries(test_xpath_wide arabica cppunit)
  add_test(xpath test_xpath -v)
  add_test(xpath_wide test_xpath_wide -v)

  add_executable(test_xslt tests/XSLT/main.cpp tests/XSLT/xslt_test.hpp)
  target_link_libraries(test_xslt arabica cppunit)
  add_executable(test_xslt_wide tests/XSLT/main_wide.cpp tests/XSLT/xslt_test.hpp)
  target_link_libraries(test_xslt_wide arabica cppunit)
  add_test(xslt test_xslt -v)
  set_tests_properties(xslt PROPERTIES SKIP_RETURN_CODE 77)
  add_test(xslt_wide test_xslt_wide -v)
  set_tests_properties(xslt_wide PROPERTIES SKIP_RETURN_CODE 77)
  endif()

if(BUILD_ARABICA_EXAMPLES)

  #
  # Example Dom writer:
  set(EXAMPLE_NAME dom_writer)
  add_executable(${EXAMPLE_NAME} examples/DOM/DOMWriter.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX pyx:
  set(EXAMPLE_NAME pyx)
  add_executable(${EXAMPLE_NAME} examples/SAX/pyx.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )

  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX simple handler:
  set(EXAMPLE_NAME simplehandler)
  set(SIMPLE_HANDLER_SOURCES
    examples/SAX/SimpleHandler.cpp
    examples/SAX/SimpleHandler.hpp
    examples/SAX/wrapper.cpp
    )
  add_executable(${EXAMPLE_NAME} ${SIMPLE_HANDLER_SOURCES})
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX taggle:
  set(EXAMPLE_NAME taggle)
  add_executable(${EXAMPLE_NAME} examples/Taggle/taggle.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX writer:
  set(EXAMPLE_NAME writer)
  add_executable(${EXAMPLE_NAME} examples/SAX/writer.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX xmlbase:
  set(EXAMPLE_NAME xmlbase)
  add_executable(${EXAMPLE_NAME} examples/SAX/xmlbase.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX transcode:
  set(EXAMPLE_NAME transcode)
  add_executable(${EXAMPLE_NAME} examples/Utils/transcode.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example SAX xgrep:
  set(EXAMPLE_NAME xgrep)
  add_executable(${EXAMPLE_NAME} examples/XPath/xgrep.cpp)
  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

  #
  # Example XSLT xgrep:
  set(EXAMPLE_NAME mangle)
  add_executable(${EXAMPLE_NAME} examples/XSLT/mangle.cpp)

  #
  # win32 disable incremental linking
  if(WIN32)
    set_property(TARGET ${EXAMPLE_NAME}
      APPEND PROPERTY COMPILE_FLAGS
      "/bigobj"
      )
  endif()

  target_link_libraries(${EXAMPLE_NAME}
    arabica
    )
  set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "3rdparty/arabica_examples")

endif()

include(CPack)


