#ifndef ARABICA_SAX_TAGGLE_HTML_SCANNER_HPP
#define ARABICA_SAX_TAGGLE_HTML_SCANNER_HPP
  
#include <SAX/SAXException.hpp>
#include <SAX/Locator.hpp>
#include <XML/XMLCharacterClasses.hpp>
#include "../Scanner.hpp"

namespace Arabica
{

namespace SAX
{

/**
This class implements a table-driven scanner for HTML, allowing for lots of
defects.  It implements the Scanner interface, which accepts a Reader
object to fetch characters from and a ScanHandler object to report lexical
events to.

Based on code from John Cowan's super TagSoup package
*/
class HTMLScanner : public Scanner, public SAX::Locator<std::string>
{
private:
  // Start of state table
  static const int S_ANAME = 1;
  static const int S_APOS = 2;
  static const int S_AVAL = 3;
  static const int S_BB = 4;
  static const int S_BBC = 5;
  static const int S_BBCD = 6;
  static const int S_BBCDA = 7;
  static const int S_BBCDAT = 8;
  static const int S_BBCDATA = 9;
  static const int S_CDATA = 10;
  static const int S_CDATA2 = 11;
  static const int S_CDSECT = 12;
  static const int S_CDSECT1 = 13;
  static const int S_CDSECT2 = 14;
  static const int S_COM = 15;
  static const int S_COM2 = 16;
  static const int S_COM3 = 17;
  static const int S_COM4 = 18;
  static const int S_DECL = 19;
  static const int S_DECL2 = 20;
  static const int S_DONE = 21;
  static const int S_EMPTYTAG = 22;
  static const int S_ENT = 23;
  static const int S_EQ = 24;
  static const int S_ETAG = 25;
  static const int S_GI = 26;
  static const int S_NCR = 27;
  static const int S_PCDATA = 28;
  static const int S_PI = 29;
  static const int S_PITARGET = 30;
  static const int S_QUOT = 31;
  static const int S_STAGC = 32;
  static const int S_TAG = 33;
  static const int S_TAGWS = 34;
  static const int S_XNCR = 35;
  static const int A_ADUP = 1;
  static const int A_ADUP_SAVE = 2;
  static const int A_ADUP_STAGC = 3;
  static const int A_ANAME = 4;
  static const int A_ANAME_ADUP = 5;
  static const int A_ANAME_ADUP_STAGC = 6;
  static const int A_AVAL = 7;
  static const int A_AVAL_STAGC = 8;
  static const int A_CDATA = 9;
  static const int A_CMNT = 10;
  static const int A_DECL = 11;
  static const int A_EMPTYTAG = 12;
  static const int A_ENTITY = 13;
  static const int A_ENTITY_START = 14;
  static const int A_ETAG = 15;
  static const int A_GI = 16;
  static const int A_GI_STAGC = 17;
  static const int A_LT = 18;
  static const int A_LT_PCDATA = 19;
  static const int A_MINUS = 20;
  static const int A_MINUS2 = 21;
  static const int A_MINUS3 = 22;
  static const int A_PCDATA = 23;
  static const int A_PI = 24;
  static const int A_PITARGET = 25;
  static const int A_PITARGET_PI = 26;
  static const int A_SAVE = 27;
  static const int A_SKIP = 28;
  static const int A_SP = 29;
  static const int A_STAGC = 30;
  static const int A_UNGET = 31;
  static const int A_UNSAVE_PCDATA = 32;
  static const int statetable[]; 
  static const std::string debug_actionnames[];
  static const std::string debug_statenames[];
  // End of state table
  static const int WinCharMap[]; // Windows char map
  static const std::string hexLetters;

  std::string publicId_;      // Locator state
  std::string systemId_;
  int lastLine_;
  int lastColumn_;
  int currentLine_;
  int currentColumn_;

  int state_;          // Current state
  int nextState_;        // Next state
  std::string outputBuffer_;  // Output buffer

  // Compensate for bug in PushbackReader that allows
  // pushing back EOF.
  //void unread(PushbackReader r, int c) throws IOException {
  //  if (c != -1) r.unread(c);
  //  }

public:
  HTMLScanner() :
      publicId_(),
      systemId_(),
      lastLine_(0),
      lastColumn_(0),
      currentLine_(0),
      currentColumn_(0),
      state_(0),
      nextState_(0),
      outputBuffer_()
  {
    outputBuffer_.reserve(200);
  } // HTMLScanner

  // Locator implementation
  int getLineNumber() const
  {
    return lastLine_;
  } // getLineNumber

  int getColumnNumber() const
  {
    return lastColumn_;
  } // getColumnNumber

  std::string getPublicId() const 
  {
    return publicId_;
  } // getPublicId

  std::string getSystemId() const
  {
    return systemId_;
  } // getSystemId


  // Scanner implementation
  /**
  Reset document locator, supplying systemid and publicid.
  @param systemid System id
  @param publicid Public id
  */
  virtual void resetDocumentLocator(const std::string& publicid, const std::string& systemid)
  {
    publicId_ = publicid;
    systemId_ = systemid;
    lastLine_ = lastColumn_ = currentLine_ = currentColumn_ = 0;
  } // resetDocumentLocator

  /**
  Scan HTML source, reporting lexical events.
  @param r0 Reader that provides characters
  @param h ScanHandler that accepts lexical events.
  */
  virtual void scan(std::istream& r, ScanHandler& h)
  {
    state_ = S_PCDATA;
/*    PushbackReader r;
    if (r0 instanceof PushbackReader) {
      r = (PushbackReader)r0;
      }
    else if (r0 instanceof BufferedReader) {
      r = new PushbackReader(r0);
      }
    else {
      r = new PushbackReader(new BufferedReader(r0));
      }
*/
//    int firstChar = r.read();  // Remove any leading BOM
//    if (firstChar != '\uFEFF') unread(r, firstChar);

    while (state_ != S_DONE) 
    {
      int ch = r.get();

      // Process control characters
      //if (ch >= 0x80 && ch <= 0x9F) 
        //ch = WinCharMap[ch-0x80];

      if (ch == '\r') 
      {
        ch = r.get();    // expect LF next
        if (ch != '\n') 
        {
          r.unget();
          ch = '\n';
        }
      }

      if (ch == '\n') 
      {
        ++currentLine_;
        currentColumn_ = 0;
      }
      else 
      {
        ++currentColumn_;
      }

      if (!(ch >= 0x20 || ch == '\n' || ch == '\t' || ch == -1)) 
        continue;

      // Search state table
      int action = 0;
      for (int i = 0; statetable[i] != -1; i += 4) 
      {
        if (state_ != statetable[i]) 
        {
          if (action != 0) 
            break;
          continue;
        }
        if (statetable[i+1] == 0) 
        {
          action = statetable[i+2];
          nextState_ = statetable[i+3];
        }
        else if (statetable[i+1] == ch) 
        {
          action = statetable[i+2];
          nextState_ = statetable[i+3];
          break;
        }
      } // for ...

      switch (action) 
      {
        case 0:
          {
            std::ostringstream os;
            os << "HTMLScanner can't cope with " << ch << " in state " << state_;
            throw std::runtime_error(os.str());
          }
         case A_ADUP:
          h.adup(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_ADUP_SAVE:
          h.adup(outputBuffer_);
          outputBuffer_.clear();
          save(ch, h);
          break;
        case A_ADUP_STAGC:
          h.adup(outputBuffer_);
          outputBuffer_.clear();
          h.stagc(outputBuffer_);
          break;
        case A_ANAME:
          h.aname(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_ANAME_ADUP:
          h.aname(outputBuffer_);
          outputBuffer_.clear();
          h.adup(outputBuffer_);
          break;
        case A_ANAME_ADUP_STAGC:
          h.aname(outputBuffer_);
          outputBuffer_.clear();
          h.adup(outputBuffer_);
          h.stagc(outputBuffer_);
          break;
        case A_AVAL:
          h.aval(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_AVAL_STAGC:
          h.aval(outputBuffer_);
          outputBuffer_.clear();
          h.stagc(outputBuffer_);
          break;
        case A_CDATA:
          mark();
          // suppress the final "]]" in the buffer
          if (outputBuffer_.size() > 1) 
            outputBuffer_.erase(outputBuffer_.size()-2);
          h.pcdata(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_ENTITY_START:
          h.pcdata(outputBuffer_);
          outputBuffer_.clear();
          save(ch, h);
          break;
        case A_ENTITY:
          {
            mark();
            char ch1 = (char)ch;
  //        System.out.println("Got " + ch1 + " in state " + ((state_ == S_ENT) ? "S_ENT" : ((state_ == S_NCR) ? "S_NCR" : "UNK")));
            if (state_ == S_ENT && ch1 == '#') 
            {
              nextState_ = S_NCR;
              save(ch, h);
              break;
            }
            else if (state_ == S_NCR && (ch1 == 'x' || ch1 == 'X')) 
            {
              nextState_ = S_XNCR;
              save(ch, h);
              break;
            }
            else if (state_ == S_ENT && XML::is_letter_or_digit(ch1)) 
            {
              save(ch, h);
              break;
            }
            else if (state_ == S_NCR && XML::is_digit(ch1)) 
            {
              save(ch, h);
              break;
            }
            else if (state_ == S_XNCR && (XML::is_digit(ch1) || hexLetters.find(ch1) != std::string::npos)) 
            {
              save(ch, h);
              break;
            }

            // The whole entity reference has been collected
            h.entity(outputBuffer_.substr(1, outputBuffer_.size()-1));
            int ent = h.getEntity();
            if (ent != 0) 
            {
              outputBuffer_.clear();
              if (ent >= 0x80 && ent <= 0x9F) 
              {
                //ent = WinCharMap[ent-0x80];
              }
              if (ent < 0x20) 
              {
                // Control becomes space
                ent = 0x20;
              }
              else if (ent >= 0xD800 && ent <= 0xDFFF) 
              {
                // Surrogates get dropped
                ent = 0;
              }
              else if (ent <= 0xFFFF) 
              {
                // BMP character
                save(ent, h);
              }
              else 
              {
                // Astral converted to two surrogates
                ent -= 0x10000;
                save((ent>>10) + 0xD800, h);
                save((ent&0x3FF) + 0xDC00, h);
              }
              if (ch != ';') 
              {
                r.unget();
                currentColumn_--;
              }
            }
            else 
            {
              r.unget();
              currentColumn_--;
            }
            nextState_ = S_PCDATA;
          } // case A_ENTITY:
          break;
        case A_ETAG:
          h.etag(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_DECL:
          h.decl(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_GI:
          h.gi(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_GI_STAGC:
          h.gi(outputBuffer_);
          outputBuffer_.clear();
          h.stagc(outputBuffer_);
          break;
        case A_LT:
          mark();
          save('<', h);
          save(ch, h);
          break;
        case A_LT_PCDATA:
          mark();
          save('<', h);
          h.pcdata(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_PCDATA:
          mark();
          h.pcdata(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_CMNT:
          mark();
          h.cmnt(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_MINUS3:
          save('-', h);
          save(' ', h);
          break;
        case A_MINUS2:
          save('-', h);
          save(' ', h);
          // fall through into A_MINUS
        case A_MINUS:
          save('-', h);
          save(ch, h);
          break;
        case A_PI:
          mark();
          h.pi(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_PITARGET:
          h.pitarget(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_PITARGET_PI:
          h.pitarget(outputBuffer_);
          outputBuffer_.clear();
          h.pi(outputBuffer_);
          break;
        case A_SAVE:
          save(ch, h);
          break;
        case A_SKIP:
          break;
        case A_SP:
          save(' ', h);
          break;
        case A_STAGC:
          h.stagc(outputBuffer_);
          outputBuffer_.clear();
          break;
        case A_EMPTYTAG:
          mark();
          if (outputBuffer_.size() > 0) 
            h.gi(outputBuffer_);
          outputBuffer_.clear();
          h.stage(outputBuffer_);
          break;
        case A_UNGET:
          r.unget();
          currentColumn_--;
          break;
        case A_UNSAVE_PCDATA:
         if (outputBuffer_.size() > 0) 
           outputBuffer_.erase(outputBuffer_.size()-1);
          h.pcdata(outputBuffer_);
          outputBuffer_.clear();
          break;
        default:
          throw std::runtime_error("Can't process state " + action);
      } // switch ...
      state_ = nextState_;
    } // while (state_ != S_DONE) 
    h.eof("");
  } // scan

  /**
  A callback for the ScanHandler that allows it to force
  the lexer state to CDATA content (no markup is recognized except
  the end of element.
  */
  void startCDATA() 
  { 
    nextState_ = S_CDATA; 
  } // startCDATA

private:
  /**
  * Mark the current scan position as a "point of interest" - start of a tag,
  * cdata, processing instruction etc.
  */
  void mark() 
  {
    lastColumn_ = currentColumn_;
    lastLine_ = currentLine_;
  } // mark

  void save(int ch, ScanHandler& h)
  {
    if (outputBuffer_.size() >= outputBuffer_.capacity() - 20) 
    {
      if (state_ == S_PCDATA || state_ == S_CDATA) 
      {
        // Return a buffer-sized chunk of PCDATA
        h.pcdata(outputBuffer_);
        outputBuffer_.clear();
      }
    }
    outputBuffer_ += static_cast<char>(ch);
  } // save

  static std::string nicechar(int in) 
  {
    if (in == '\n') 
      return "\\n";
    std::ostringstream os;
    if(in >= 32) 
      os << '\'' << static_cast<char>(in) << '\'';
    else
      os << std::hex << std::showbase << in;
    return os.str();
  } // nicechar

  HTMLScanner(const HTMLScanner&);
  bool operator==(const HTMLScanner&) const;
  HTMLScanner& operator=(const HTMLScanner&);
}; // class HTMLScanner

const int HTMLScanner::statetable[] = {
    S_ANAME, '/', A_ANAME_ADUP, S_EMPTYTAG,
    S_ANAME, '=', A_ANAME, S_AVAL,
    S_ANAME, '>', A_ANAME_ADUP_STAGC, S_PCDATA,
    S_ANAME, 0, A_SAVE, S_ANAME,
    S_ANAME, -1, A_ANAME_ADUP_STAGC, S_DONE,
    S_ANAME, ' ', A_ANAME, S_EQ,
    S_ANAME, '\n', A_ANAME, S_EQ,
    S_ANAME, '\t', A_ANAME, S_EQ,
    S_APOS, '\'', A_AVAL, S_TAGWS,
    S_APOS, 0, A_SAVE, S_APOS,
    S_APOS, -1, A_AVAL_STAGC, S_DONE,
    S_APOS, ' ', A_SP, S_APOS,
    S_APOS, '\n', A_SP, S_APOS,
    S_APOS, '\t', A_SP, S_APOS,
    S_AVAL, '\'', A_SKIP, S_APOS,
    S_AVAL, '"', A_SKIP, S_QUOT,
    S_AVAL, '>', A_AVAL_STAGC, S_PCDATA,
    S_AVAL, 0, A_SAVE, S_STAGC,
    S_AVAL, -1, A_AVAL_STAGC, S_DONE,
    S_AVAL, ' ', A_SKIP, S_AVAL,
    S_AVAL, '\n', A_SKIP, S_AVAL,
    S_AVAL, '\t', A_SKIP, S_AVAL,
    S_BB, 'C', A_SKIP, S_BBC,
    S_BB, 0, A_SKIP, S_DECL,
    S_BB, -1, A_SKIP, S_DONE,
    S_BBC, 'D', A_SKIP, S_BBCD,
    S_BBC, 0, A_SKIP, S_DECL,
    S_BBC, -1, A_SKIP, S_DONE,
    S_BBCD, 'A', A_SKIP, S_BBCDA,
    S_BBCD, 0, A_SKIP, S_DECL,
    S_BBCD, -1, A_SKIP, S_DONE,
    S_BBCDA, 'T', A_SKIP, S_BBCDAT,
    S_BBCDA, 0, A_SKIP, S_DECL,
    S_BBCDA, -1, A_SKIP, S_DONE,
    S_BBCDAT, 'A', A_SKIP, S_BBCDATA,
    S_BBCDAT, 0, A_SKIP, S_DECL,
    S_BBCDAT, -1, A_SKIP, S_DONE,
    S_BBCDATA, '[', A_SKIP, S_CDSECT,
    S_BBCDATA, 0, A_SKIP, S_DECL,
    S_BBCDATA, -1, A_SKIP, S_DONE,
    S_CDATA, '<', A_SAVE, S_CDATA2,
    S_CDATA, 0, A_SAVE, S_CDATA,
    S_CDATA, -1, A_PCDATA, S_DONE,
    S_CDATA2, '/', A_UNSAVE_PCDATA, S_ETAG,
    S_CDATA2, 0, A_SAVE, S_CDATA,
    S_CDATA2, -1, A_UNSAVE_PCDATA, S_DONE,
    S_CDSECT, ']', A_SAVE, S_CDSECT1,
    S_CDSECT, 0, A_SAVE, S_CDSECT,
    S_CDSECT, -1, A_SKIP, S_DONE,
    S_CDSECT1, ']', A_SAVE, S_CDSECT2,
    S_CDSECT1, 0, A_SAVE, S_CDSECT,
    S_CDSECT1, -1, A_SKIP, S_DONE,
    S_CDSECT2, '>', A_CDATA, S_PCDATA,
    S_CDSECT2, 0, A_SAVE, S_CDSECT,
    S_CDSECT2, -1, A_SKIP, S_DONE,
    S_COM, '-', A_SKIP, S_COM2,
    S_COM, 0, A_SAVE, S_COM2,
    S_COM, -1, A_CMNT, S_DONE,
    S_COM2, '-', A_SKIP, S_COM3,
    S_COM2, 0, A_SAVE, S_COM2,
    S_COM2, -1, A_CMNT, S_DONE,
    S_COM3, '-', A_SKIP, S_COM4,
    S_COM3, 0, A_MINUS, S_COM2,
    S_COM3, -1, A_CMNT, S_DONE,
    S_COM4, '-', A_MINUS3, S_COM4,
    S_COM4, '>', A_CMNT, S_PCDATA,
    S_COM4, 0, A_MINUS2, S_COM2,
    S_COM4, -1, A_CMNT, S_DONE,
    S_DECL, '-', A_SKIP, S_COM,
    S_DECL, '[', A_SKIP, S_BB,
    S_DECL, '>', A_SKIP, S_PCDATA,
    S_DECL, 0, A_SAVE, S_DECL2,
    S_DECL, -1, A_SKIP, S_DONE,
    S_DECL2, '>', A_DECL, S_PCDATA,
    S_DECL2, 0, A_SAVE, S_DECL2,
    S_DECL2, -1, A_SKIP, S_DONE,
    S_EMPTYTAG, '>', A_EMPTYTAG, S_PCDATA,
    S_EMPTYTAG, 0, A_SAVE, S_ANAME,
    S_EMPTYTAG, ' ', A_SKIP, S_TAGWS,
    S_EMPTYTAG, '\n', A_SKIP, S_TAGWS,
    S_EMPTYTAG, '\t', A_SKIP, S_TAGWS,
    S_ENT, 0, A_ENTITY, S_ENT,
    S_ENT, -1, A_ENTITY, S_DONE,
    S_EQ, '=', A_SKIP, S_AVAL,
    S_EQ, '>', A_ADUP_STAGC, S_PCDATA,
    S_EQ, 0, A_ADUP_SAVE, S_ANAME,
    S_EQ, -1, A_ADUP_STAGC, S_DONE,
    S_EQ, ' ', A_SKIP, S_EQ,
    S_EQ, '\n', A_SKIP, S_EQ,
    S_EQ, '\t', A_SKIP, S_EQ,
    S_ETAG, '>', A_ETAG, S_PCDATA,
    S_ETAG, 0, A_SAVE, S_ETAG,
    S_ETAG, -1, A_ETAG, S_DONE,
    S_ETAG, ' ', A_SKIP, S_ETAG,
    S_ETAG, '\n', A_SKIP, S_ETAG,
    S_ETAG, '\t', A_SKIP, S_ETAG,
    S_GI, '/', A_SKIP, S_EMPTYTAG,
    S_GI, '>', A_GI_STAGC, S_PCDATA,
    S_GI, 0, A_SAVE, S_GI,
    S_GI, -1, A_SKIP, S_DONE,
    S_GI, ' ', A_GI, S_TAGWS,
    S_GI, '\n', A_GI, S_TAGWS,
    S_GI, '\t', A_GI, S_TAGWS,
    S_NCR, 0, A_ENTITY, S_NCR,
    S_NCR, -1, A_ENTITY, S_DONE,
    S_PCDATA, '&', A_ENTITY_START, S_ENT,
    S_PCDATA, '<', A_PCDATA, S_TAG,
    S_PCDATA, 0, A_SAVE, S_PCDATA,
    S_PCDATA, -1, A_PCDATA, S_DONE,
    S_PI, '>', A_PI, S_PCDATA,
    S_PI, 0, A_SAVE, S_PI,
    S_PI, -1, A_PI, S_DONE,
    S_PITARGET, '>', A_PITARGET_PI, S_PCDATA,
    S_PITARGET, 0, A_SAVE, S_PITARGET,
    S_PITARGET, -1, A_PITARGET_PI, S_DONE,
    S_PITARGET, ' ', A_PITARGET, S_PI,
    S_PITARGET, '\n', A_PITARGET, S_PI,
    S_PITARGET, '\t', A_PITARGET, S_PI,
    S_QUOT, '"', A_AVAL, S_TAGWS,
    S_QUOT, 0, A_SAVE, S_QUOT,
    S_QUOT, -1, A_AVAL_STAGC, S_DONE,
    S_QUOT, ' ', A_SP, S_QUOT,
    S_QUOT, '\n', A_SP, S_QUOT,
    S_QUOT, '\t', A_SP, S_QUOT,
    S_STAGC, '>', A_AVAL_STAGC, S_PCDATA,
    S_STAGC, 0, A_SAVE, S_STAGC,
    S_STAGC, -1, A_AVAL_STAGC, S_DONE,
    S_STAGC, ' ', A_AVAL, S_TAGWS,
    S_STAGC, '\n', A_AVAL, S_TAGWS,
    S_STAGC, '\t', A_AVAL, S_TAGWS,
    S_TAG, '!', A_SKIP, S_DECL,
    S_TAG, '?', A_SKIP, S_PITARGET,
    S_TAG, '/', A_SKIP, S_ETAG,
    S_TAG, '<', A_SAVE, S_TAG,
    S_TAG, 0, A_SAVE, S_GI,
    S_TAG, -1, A_LT_PCDATA, S_DONE,
    S_TAG, ' ', A_LT, S_PCDATA,
    S_TAG, '\n', A_LT, S_PCDATA,
    S_TAG, '\t', A_LT, S_PCDATA,
    S_TAGWS, '/', A_SKIP, S_EMPTYTAG,
    S_TAGWS, '>', A_STAGC, S_PCDATA,
    S_TAGWS, 0, A_SAVE, S_ANAME,
    S_TAGWS, -1, A_STAGC, S_DONE,
    S_TAGWS, ' ', A_SKIP, S_TAGWS,
    S_TAGWS, '\n', A_SKIP, S_TAGWS,
    S_TAGWS, '\t', A_SKIP, S_TAGWS,
    S_XNCR, 0, A_ENTITY, S_XNCR,
    S_XNCR, -1, A_ENTITY, S_DONE,
    -1, -1, -1, -1
}; // HTMLScanner::statetable

const std::string HTMLScanner::debug_actionnames[] = { "", "A_ADUP", "A_ADUP_SAVE", "A_ADUP_STAGC", "A_ANAME", "A_ANAME_ADUP", "A_ANAME_ADUP_STAGC", "A_AVAL", "A_AVAL_STAGC", "A_CDATA", "A_CMNT", "A_DECL", "A_EMPTYTAG", "A_ENTITY", "A_ENTITY_START", "A_ETAG", "A_GI", "A_GI_STAGC", "A_LT", "A_LT_PCDATA", "A_MINUS", "A_MINUS2", "A_MINUS3", "A_PCDATA", "A_PI", "A_PITARGET", "A_PITARGET_PI", "A_SAVE", "A_SKIP", "A_SP", "A_STAGC", "A_UNGET", "A_UNSAVE_PCDATA"};
const std::string HTMLScanner::debug_statenames[] = { "", "S_ANAME", "S_APOS", "S_AVAL", "S_BB", "S_BBC", "S_BBCD", "S_BBCDA", "S_BBCDAT", "S_BBCDATA", "S_CDATA", "S_CDATA2", "S_CDSECT", "S_CDSECT1", "S_CDSECT2", "S_COM", "S_COM2", "S_COM3", "S_COM4", "S_DECL", "S_DECL2", "S_DONE", "S_EMPTYTAG", "S_ENT", "S_EQ", "S_ETAG", "S_GI", "S_NCR", "S_PCDATA", "S_PI", "S_PITARGET", "S_QUOT", "S_STAGC", "S_TAG", "S_TAGWS", "S_XNCR"};

const int HTMLScanner::WinCharMap[] = {        // Windows chars map
    0x20AC, 0xFFFD, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0xFFFD, 0x017D, 0xFFFD,
    0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0xFFFD, 0x017E, 0x0178
}; // HTMLScanner::WinCharMap

const std::string HTMLScanner::hexLetters = "abcdefABCDEF";

} // namespace SAX

} // namespace Arabica

#endif

