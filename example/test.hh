/*!
 * @header	test.hh
 *		All definitions used by HeaderBrowser "parser".
 * @abstract	Character and string definitions for HB XML parse.
 * @author	Amaury Bouchard <amaury@amaury.net>
 * @version	1.0 Dec 26 2000
 * @see		styx.hh
 * @link	HeaderBrowser Web Site <http://www.headerbrowser.org>
 * @link	GNU
 * @ref		styx_dom.hh
 * @author	Contact <contact@headerbrowser.org>
 */ 
#ifndef   __TEST_H__
#define   __TEST_H__

/*!
 * @var	ma
 * @abstract variable
 * @discussion ma variable
 */
int	ma;

/*!
 * @defined	TOTO
 * @abstract	macro de chaine
 * @discussion	macro contenant une chaine de caractere
 */
#define	TOTO	"toto"

/*!
 * @function	str_cpy
 * @abstract	copie des chaines
 * @discussion	fonction qui copie une chaine de caracteres dans une autre
 * @param	src Chaine source
 * @param	dst Chaine de destination
 * @result	un pointeur sur la chaine dst
 */
char	*str_cpy(char *dst, char *src);

/*!
 * @define	TUTU
 *		macro de fonction
 * @abstract	inline fonction
 */
#define	TUTU(x)	x == 1

/*!
 * @union	uneunion_u
 * ceci est une union entre plusieurs champs tres importants
 * @abstract petite union
 * @field	tutu objet toto_t
 * @field  toto objet titi_t
 */
union	uneunion_u
{
  toto_t	tutu;
  titi_t	toto;
};

/*!
 * @define	TITI
 * @abstract deuxieme macro
 * @discussion	macro remplacant une expression mathematique
 */
#define	TITI	(3 + 5 \
		- 2)

/*!
 * @var tagada
 * @abstract	encore une petite globale
 * @discussion	Ceci est une variable vitale
 */
toto_t	*tagada;

/*!
 * @class	Toto
 *		Objet d'exemple
 * @abstract	petit obj
 */
class	Toto : public titi
{
  /*!
  * @function Toto
  *		constructeur
  * @param	i entier
  * @param	j autre entier
  * @param k caractere
  * @result l'objet "cree"
  */
  Toto(int i, int j, char k);
public:
  /*! @var trululu c'est un entier */
  int	trululu;
private:
  /*! @var trilili carac */
  char trilili;
};

/*!
 * @class	MonObjetAMoi
 * @discussion	Cet objet est une demonstration de classe complete.
 * @abstract	Objet plus gros que le precedent.
 */
class	MonObjetAMoi : public Toto
{
public:
  /*!
   * @function	MonObjetAMoi
   *		Constructeur de l'objet
   * @abstract	constructeur
   * @param	moi	Un moi_t
   */
  MonObjetAMoi(moi_t moi);
private:
  /*! @var tugudu petite variable sympa */
  int	tugudu;
};

/*!
 * @typedef	status_t
 *		Toutes les valeurs de status possible sont ici
 * @abstract	Status
 * @constant	STATUS_NONE Pas de status
 * @constant	STATUS_OK Status bon
 * @constant	STATUS_ERR Erreur
 */
typedef enum	status_e
{
  STATUS_NONE = 0,
  STATUS_OK,
  STATUS_ERR
}		status_t;

/*!
 * @enum	monenum_e
 * petite enum sympathique
 * @abstract petite
 * @constant	TOTO_1 premier toto
 * @constant	TOTO_2 deuxieme toto
 * @constant	TOTO_3 troisieme toto
 */
enum	monenum_e
{
  TOTO_1, TOTO_2, TOTO_3
};

/*!
 * @struct	mastructure_s
 * @abstract	structure exemple
 * @discussion	petite structure de test
 * @field	aa caractere
 * @field	ii entier
 */
struct	mastructure_s
{
  char	aa;
  int	ii;
};

/*!
 * @typedef	skate_t
 * @abstract	definition d'un skate
 * @discussion	tout sur le skate-board 
 * @field	roues nombre de roues 
 * @field	diam Diametre des roues 
 */
typedef struct	skate_s
{
  int		roues;
  int		diam;
}		skate_t;

/*!
 * @function	toto2titi
 *		realise une conversion de toto vers titi
 * @abstract	fonction de conversion
 * @result	le nouveau titi
 * @param oo le toto initial
 * @param ii le titi servant de gabarit
 * @param env l'environnement de travail
*/
titi_t	toto2titi(toto_t oo, titi_t ii, env_t env);

/*!
 * @typedef	yoyo_t
		un type qui monte, qui monte...
@abstract	c'est le type yoyo
* @field	diametre	diametre de la ficelle
* @field	longueur	longueur de la ficelle
*/
typedef struct	yoyo_s
{
  int		diametre;
  int		longueur;
}		yoyo_t;

#endif /* __TEST_H__ */
