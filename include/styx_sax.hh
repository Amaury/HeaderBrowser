/*!
 * @header	styx_sax.hh
 * @abstract	SAX parser object definition.
 * @discussion	Contains all types and objects definitions for using a SAX type
 *		parser for XML file reading.
 * @author	Amaury Bouchard <amaury@amaury.net>
 * @version	1.0.0 Dec 23 2000
 * @see		styx.hh
 * @link	http://www.amaury.net
 * @link	http://www.headerbrowser.org
 */
#ifndef   __STYX_SAX_H__
#define   __STYX_SAX_H__

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <stdio.h>
#include "styx.hh"

/*! @defined SAX_ERR_RETURN Macro used to simplify the internal code */
#define	SAX_ERR_RETURN	{setStatus(SAX_STATUS_ERR_PARSE);\
			errorHandler(line); return ;}

/*!
 * @typedef	StyxSaxStatus
 * @discussion	Defined type for constants used as parser's status indicator.
 * @constant	SAX_STATUS_NONE No status set yet.
 * @constant	SAX_STATUS_OK No parse error.
 * @constant	SAX_STATUS_STOPPED Parser stopped by user.
 * @constant	SAX_STATUS_NO_FILE The parser couldn't read the specified file.
 * @constant	SAX_STATUS_ERR_PARSE Parsing error.
 */
typedef enum	StyxSaxStatus_e
{
  SAX_STATUS_NONE = 0,
  SAX_STATUS_OK,
  SAX_STATUS_STOPPED,
  SAX_STATUS_NO_FILE,
  SAX_STATUS_ERR_PARSE
}		StyxSaxStatus;

/*!
 * @class	StyxSaxAttr
 * @abstract	Attribute of an XML tag.
 * @discussion	all XML tag founded by the parser may contains some
 *		attributes. Each of them are stored in this object.
 */
class		StyxSaxAttr
{
public:
  /*!
   * @function	getName
   *		Use it to get the attribute's name.
   * @return	The attribute's name.
   */
  string	getName(void);
  /*!
   * @function	getValue
   *		Use it to get the attribute's value.
   * @return	The attribute's value.
   */
  string	getValue(void);
  /*!
   * @function	StyxSaxAttr
   *		Constructor.
   * @param	name The attribute's name.
   * @param	value The attribute's value.
   */
  StyxSaxAttr(string name, string value);
private:
  /*! @var name The attribute's name. */
  string	name;
  /*! @var value The attribute's value. */
  string	value;
};

/*!
 * @class	StyxSax
 * @abstract	Main object for SAX-type parsing of XML files.
 * @discussion	Super-class for SAX parsers. Sets the defaults handlers for
 *		tag parsing.
 */
class		StyxSax
{
public:
  /*!
   * @function	saxParse
   *		Do parsing of the given file.
   * @param	filename Name of the file to parse.
   * @result	The status resulting of the file parsing.
   */
  StyxSaxStatus	saxParse(char* filename);
  /*!
   * @function	saxStop
   *		Stop a SAX parse, even before the end of parsing.
   */
  void		saxStop(void);
  /*!
   * @function	StyxSax
   *		Constructor.
   */
  StyxSax(void);
  /*!
   * @function	~StyxSax
   *		Desctructor.
   */
  virtual ~StyxSax(void);
protected:
  /*!
   * @function	setStatus
   *		Change the current parser status.
   * @param	newStatus The new value of parser status.
   */
  void		setStatus(StyxSaxStatus newStatus);
  /*!
   * @function	openTagHandler
   *		Method called when an XML open tag is founded.
   * @param	name Name of the tag.
   * @param	attrs All attributes of the tag.
   */
  virtual void	openTagHandler(string name, vector<StyxSaxAttr*> attrs);
  /*!
   * @function	insideTextHandler
   *		Method called when a text character is founded between an
   *		opening and a closing tag.
   * @param	c The caracter founded.
   */
  virtual void	insideTextHandler(char c);
  /*!
   * @function	closeTagHandler
   *		Method called when an XML close tag is founded.
   * @param	name Name of the tag.
   */
  virtual void	closeTagHandler(string name);
  /*!
   * @function	commentHandler
   *		Method called when an XML comment is founded in the WML file.
   * @param	content The character string of the comment.
   */
  virtual void	commentHandler(string content);
  /*!
   * @function	processingInstructionHandler
   *		Method called when an XML processing instruction is founded.
   * @param	target Name of the processing instruction's target.
   * @param	content Character string of the instruction.
   */
  virtual void	processingInstructionHandler(string target, string content);
  /*!
   * @function	cdataHandler
   *		Method called when a CDATA tag is founded.
   * @param	content Character string of the tag.
   */
  virtual void	cdataHandler(string content);
  /*!
   * @function	errorHandler
   *		Method called when a parsing error appears.
   * @param	line Line number in th XML file where error happens.
   */
  virtual void	errorHandler(int line);
private:
  /*! @var file Pointer to the parsed file. */
  FILE*		file;
  /*! @var saxStatus Current status of the SAX parser. */
  StyxSaxStatus	saxStatus;
  /*! @var line Current line parsed in the file. */
  int		line;
  /*! @var charac Current character parsed in the line. */
  int		charac;
  /*!
   * @function	getChar
   *		Used to get the next character of parsed file.
   * @result	The next character.
   */
  char		getChar(void);
  /*!
   * @function	ungetChar
   *		Used to put back a character in the XML file stream.
   * @param	c The character to put back.
   */
  void		ungetChar(char c);
  /*!
   * @function	doOpenTag
   *		Internal function used to parse the XML file when a '<' is
   *		founded. Call the sub-parse functions.
   */
  void		doOpenTag(void);
  /*!
   * @function	parseOpenTag
   *		Internal function used to parse open tags.
   */
  void		parseOpenTag(void);
  /*!
   * @function	parseCloseTag
   *		Internal function used to parse close tags.
   */
  void		parseCloseTag(void);
  /*!
   * @function	parseProcessingInstruction
   *		Internal function used to parse processing instructions.
   */
  void		parseProcessingInstruction(void);
  /*!
   * @function	parseComment
   *		Internal function used to parse XML comments.
   */
  void		parseComment(void);
  /*!
   * @function	parseCdata
   *		Internal function used to parse CDATA tags.
   */
  void		parseCdata(void);
};

#endif /* __STYX_SAX_H__ */
