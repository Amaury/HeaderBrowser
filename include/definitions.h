#ifndef   __DEFINITIONS_H__
#define   __DEFINITIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

// character macros
#define INF                     '<'
#define SUP                     '>'
#define SLASH                   '/'
#define	BACKSLASH		'\\'
#define SPACE                   ' '
#define TAB                     '\t'
#define CR                      '\n'
#define INTERROG                '?'
#define EXCLAM                  '!'
#define MINUS                   '-'
#define EQUAL                   '='
#define DOUBLE_QUOTE            '\"'
#define LEFT_BRACE              '['
#define RIGHT_BRACE             ']'
#define OPEN_PAR                '('
#define CLOSE_PAR               ')'
#define COLON                   ':'
#define	SEMI_COLON		';'
#define STAR                    '*'
#define AT                      '@'
#define DOT                     '.'
#define PIPE                    '|'
#define	LEFT_ACCOLADE		'{'
#define	RIGHT_ACCOLADE		'}'

// string macros
#define	HB_HEADER		"header"
#define	HB_PACKAGE		"package"
#define	HB_AUTHOR		"author"
#define	HB_VERSION		"version"
#define	HB_SEE			"see"
#define	HB_REF			"ref"
#define	HB_LINK			"link"
#define	HB_ABSTRACT		"abstract"
#define	HB_SHORT		"short"
#define	HB_DISCUSSION		"discussion"
#define	HB_FUNCTION		"function"
#define	HB_PARAM		"param"
#define	HB_RESULT		"result"
#define	HB_RETURN		"return"
#define	HB_STRUCT		"struct"
#define	HB_UNION		"union"
#define	HB_FIELD		"field"
#define	HB_ENUM			"enum"
#define	HB_CONSTANT		"constant"
#define	HB_TYPEDEF		"typedef"
#define	HB_DEFINED		"defined"
#define	HB_DEFINE		"define"
#define	HB_CLASS		"class"
#define	HB_VAR			"var"
#define	COMMENT_JAVADOC_START	"/**"
#define	COMMENT_HB_START	"/*!"
#define	COMMENT_C_START		"/*"
#define	COMMENT_C_END		"*/"
#define	COMMENT_CPP		"//"

/* macro for space testing */
#define IS_SPACE(x)             (x == SPACE || x == TAB || x == CR || x == 13)
 
/* macro for number testing */
#define IS_NUMBER_CHAR(x)       (x >= '0' && x <= '9')

#ifdef __cplusplus
}
#endif

#endif /* __DEFINITIONS_H__ */
