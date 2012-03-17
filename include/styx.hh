/*!
 * @header	styx.hh
 * @abstract	Top level header file of Styx library for XML manipulation
 *		(SAX, DOM and XPath).
 * @discussion	Include this file to access all functionnalities of the Styx
 *		lib. Refere to styx_sax.hh and styx_dom.hh to know more about
 *		SAX parser, DOM tree construction, and XPath uses.
 * @author	Amaury Bouchard <amaury@amaury.net>
 * @version	1.0.0 Dec 23 2000
 * @see		styx_sax.hh
 * @see		styx_dom.hh
 */
#ifndef   __STYX_H__
#define   __STYX_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef	__STYX_SAX_H__
#include "styx_sax.hh"
#include "styx_dom.hh"
#endif

/*! @defined XML String at the begining of XML file */
#define	XML			"xml"
/*! @defined XML_VERSION Setting the XML's version definition */
#define	XML_VERSION		"version"
/*! @defined ENCODING Setting the XML's characters set definition */
#define	ENCODING		"encoding"
/*! @defined STANDALONE Setting the use of DTD */
#define	STANDALONE		"standalone"
/*! @defined CDATA XML'sCDATA tag definition */
#define	CDATA			"CDATA"
/*! @defined XMLNS String for XML namespace definition */
#define	XMLNS			"xmlns"

#define	STYX_SPACE		' '
#define	STYX_TAB		'\t'
#define	STYX_CR			'\n'
#define	STYX_INF		'<'
#define	STYX_SUP		'>'
#define	STYX_EQUAL		'='
#define	STYX_DOUBLE_QUOTE	'\"'
#define	STYX_INTERROG		'?'
#define	STYX_EXCLAM		'!'
#define	STYX_SLASH		'/'
#define	STYX_MINUS		'-'
#define	STYX_LEFT_BRACE		'['
#define	STYX_RIGHT_BRACE	']'
#define	STYX_COLON		':'
#define	STYX_AT			'@'
#define	STYX_PIPE		'|'
#define	STYX_OPEN_PAR		'('
#define	STYX_CLOSE_PAR		')'
#define	STYX_DOT		'.'
#define	STYX_STAR		'*'

/*! @defined STYX_IS_SPACE True if a character is a spacing character */
#define	STYX_IS_SPACE(x)	(x == STYX_SPACE || x == STYX_TAB || \
				x == STYX_CR)

#endif /* __STYX_H__ */
