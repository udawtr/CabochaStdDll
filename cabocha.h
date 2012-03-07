/*
  CaboCha -- Yet Another Japanese Dependency Structure Analyzer

  $Id: cabocha.h,v 1.44 2005/12/24 12:30:35 taku Exp $;

  Copyright (C) 2000-2004 Taku Kudo <taku-ku@is.aist-nara.ac.jp>
  This is free software with ABSOLUTELY NO WARRANTY.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _CABOCHA_CABOCHA_H
#define _CABOCHA_CABOCHA_H

#ifdef __cplusplus

/* for C */
extern "C" {
#endif

#ifdef _WIN32
#  ifdef DLL_EXPORT
#    define CABOCHA_DLL_EXTERN    __declspec(dllexport)
#  else
#    ifdef  DLL_IMPORT
#      define CABOCHA_DLL_EXTERN  __declspec(dllimport)
#    endif
#  endif
#endif

#ifndef CABOCHA_DLL_EXTERN
#  define CABOCHA_DLL_EXTERN extern
#endif

#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif

  typedef struct _cabocha_t cabocha_t;

  typedef void cabocha_tree_t;

  struct _cabocha_chunk_t
  {
    int link;
    size_t head;
    size_t func;
    double score;
    char  *rel;
    char  *feature[128];
  };

  struct _cabocha_token_t
  {
    char *surface;
    char *read;
    char *base;
    char *pos;
    char *pos_list[8];
    char *cform;
    char *ctype;
    char *ne;
    char *optional;
    int  status;
    struct _cabocha_chunk_t *chunk;
  };


  typedef struct _cabocha_chunk_t cabocha_chunk_t;
  typedef struct _cabocha_token_t cabocha_token_t;

  //CABOCHA_DLL_EXTERN int        cabocha_do            (int, char **);
  //CABOCHA_DLL_EXTERN cabocha_t *cabocha_new           (int, char **);
  //CABOCHA_DLL_EXTERN cabocha_t *cabocha_new2          (char *);
  //CABOCHA_DLL_EXTERN char      *cabocha_strerror      (cabocha_t*);
  //CABOCHA_DLL_EXTERN char      *cabocha_sparse_tostr  (cabocha_t *, char *);
  //CABOCHA_DLL_EXTERN char      *cabocha_sparse_tostr2 (cabocha_t*,  char*, size_t);
  //CABOCHA_DLL_EXTERN char      *cabocha_sparse_tostr3 (cabocha_t*,  char*, size_t, char *, size_t);
  //CABOCHA_DLL_EXTERN void       cabocha_destroy       (cabocha_t *);
  //CABOCHA_DLL_EXTERN cabocha_tree_t   *cabocha_sparse_totree   (cabocha_t*, char*);
  //CABOCHA_DLL_EXTERN cabocha_tree_t   *cabocha_sparse_totree2  (cabocha_t*, char*, size_t);
  //CABOCHA_DLL_EXTERN size_t      cabocha_tree_size       (cabocha_tree_t*);
  //CABOCHA_DLL_EXTERN cabocha_token_t  *cabocha_tree_get_token  (cabocha_tree_t*, size_t);
  //CABOCHA_DLL_EXTERN char             *cabocha_tree_tostr  (cabocha_tree_t*, int);
  //CABOCHA_DLL_EXTERN char             *cabocha_tree_tostr2 (cabocha_tree_t*, int, char *, size_t);

#ifdef __cplusplus
}
#endif

/* for C++ */
#ifdef __cplusplus
#include <string>
#include <vector>
#include <iostream>
#include <strstream>

namespace CaboCha
{
  enum { PARSER_MODE, SELECTION_MODE };
  enum { FORMAT_TREE, FORMAT_LATTICE, FORMAT_TREE_LATTICE, FORMAT_XML, FORMAT_NONE };
  enum { INPUT_RAW_SENTENCE, INPUT_POS, INPUT_CHUNK, INPUT_SELECTION, INPUT_PARSE };
  enum { OUTPUT_RAW_SENTENCE, OUTPUT_POS, OUTPUT_CHUNK, OUTPUT_SELECTION, OUTPUT_PARSE };
  enum { TOKEN_ANY, TOKEN_BEGIN, TOKEN_NEVER };
  enum { WITHOUT_NE, NE_WITH_CONSTRAINT, NE_WITHOUT_CONSTRAINT };

  typedef struct _cabocha_chunk_t Chunk;
  typedef struct _cabocha_token_t Token;

  class Param;
  template <class T> class FreeList;

  class Tree: public std::vector <Token>
  {
  private:
    FreeList<char>  *freelist1;
    FreeList<Chunk> *freelist2;
    std::ostrstream *ostrs;

    std::ostream& writeLattice (std::ostream &, int);
    std::ostream& writeTree    (std::ostream &, int);
    std::ostream& writeXML     (std::ostream &, int);

  public:
    std::string sentence;
    int outputLayer;

    std::istream& read  (std::istream &, int = 0);
    std::ostream& write (std::ostream &, int = 0, int = 0);
    void clear ();

    Token *getToken (size_t i) { return &(*this)[i]; }
    const char *toString  (int);
    const char *toString  (int, char *, size_t);

    char *alloc (size_t);
    char *alloc (char *);
    Chunk *allocChunk ();

    Tree ();
    ~Tree ();
  };

  class Analyzer;

  class Parser
  {
  private:
    std::vector <Analyzer *> analyzer;
    Tree   *tree;
    int    outputFormat;
    int    inputLayer;
    int    outputLayer;
    std::string _what;

    Tree   *parse (Tree *);

  public:
    bool       open   (Param &);
    bool       open   (int, char**);
    bool       open   (const char*);
    bool       close  ();

    int        parse           (int, char **);
    int        parse           (std::istream&, std::ostream &);
    Tree       *parse          (std::istream&);
    Tree       *parse          (const char*, size_t = 0);
    const char *parseToString  (const char*, size_t = 0);
    const char *parseToString  (const char*, size_t, char*, size_t);
    const char *what ();

    Parser ();
    Parser (const char *);
    Parser (int, char **);
    Parser (Param &);
    ~Parser ();
  };
}
#endif
#endif
