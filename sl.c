/*
 * かなローマ字変換をするプログラム
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <stdbool.h>
#include  <ctype.h>

static  char  *tab[]={
        "a"  ,"あ"  ,"i"  ,"い"  ,"u"  ,"う"  ,"e"  ,"え"  ,"o"  ,"お"  ,
        "va" ,"う゛ぁ","vi","う゛ぃ","vu","う゛","ve","う゛ぇ","vo","う゛ぉ",
        "ja" ,"じゃ",      "ju" ,"じゅ","je" ,"じぇ","jo" ,"じょ",
        "jya","じゃ","jyi","じぃ","jyu","じゅ","jye","じぇ","jyo","じょ",
        "kya","きゃ","kyi","きぃ","kyu","きゅ","kye","きぇ","kyo","きょ",
        "sha","しゃ","shi","しぃ","shu","しゅ","she","しぇ","sho","しょ",
        "sya","しゃ","syi","しぃ","syu","しゅ","sye","しぇ","syo","しょ",
        "cha","ちゃ","chi","ち"  ,"chu","ちゅ","che","ちぇ","cho","ちょ",
        "cya","ちゃ","cyi","ちぃ","cyu","ちゅ","cye","ちぇ","cyo","ちょ",
        "ta" ,"た"  ,"chi","ち"  ,"tsu","つ"  ,"te" ,"て"  ,"to" ,"と"  ,
        "nya","にゃ","nyi","にぃ","nyu","にゅ","nye","にぇ","nyo","にょ",
        "hya","ひゃ","hyi","ひぃ","hyu","ひゅ","hye","ひぇ","hyo","ひょ",
        "fa" ,"ふぁ","fi" ,"ふぃ","fu" ,"ふ",  "fe" ,"ふぇ","fo" ,"ふぉ",
        "mya","みゃ","myi","みぃ","myu","みゅ","mye","みぇ","myo","みょ",
        "rya","りゃ","ryi","りぃ","ryu","りゅ","rye","りぇ","ryo","りょ",
        "gya","ぎゃ","gyi","ぎぃ","gyu","ぎゅ","gye","ぎぇ","gyo","ぎょ",
        "dya","ぢゃ","dyi","ぢぃ","dyu","ぢゅ","dye","ぢぇ","dyo","ぢょ",
        "bya","びゃ","byi","びぃ","byu","びゅ","bye","びぇ","byo","びょ",
        "pya","ぴゃ","pyi","ぴぃ","pyu","ぴゅ","pye","ぴぇ","pyo","ぴょ",
        "ka" ,"か"  ,"ki" ,"き"  ,"ku" ,"く"  ,"ke" ,"け"  ,"ko" ,"こ"  ,
        "sa" ,"さ"  ,"shi","し"  ,"su" ,"す"  ,"se" ,"せ"  ,"so" ,"そ"  ,
        "na" ,"な"  ,"ni" ,"に"  ,"nu" ,"ぬ"  ,"ne" ,"ね"  ,"no" ,"の"  ,
        "ha" ,"は"  ,"hi" ,"ひ"  ,"hu" ,"ふ"  ,"he" ,"へ"  ,"ho" ,"ほ"  ,
        "ma" ,"ま"  ,"mi" ,"み"  ,"mu" ,"む"  ,"me" ,"め"  ,"mo" ,"も"  ,
        "ya" ,"や"  ,"yi" ,"ゐ"  ,"yu" ,"ゆ"  ,"ye" ,"ゑ"  ,"yo" ,"よ"  ,
        "ra" ,"ら"  ,"ri" ,"り"  ,"ru" ,"る"  ,"re" ,"れ"  ,"ro" ,"ろ"  ,
        "wa" ,"わ"  ,"wi" ,"うぃ","wu" ,"うぅ","we" ,"うぇ","wo" ,"を"  ,
        "ga" ,"が"  ,"gi" ,"ぎ"  ,"gu" ,"ぐ"  ,"ge" ,"げ"  ,"go" ,"ご"  ,
        "za" ,"ざ"  ,"ji" ,"じ"  ,"zu" ,"ず"  ,"ze" ,"ぜ"  ,"zo" ,"ぞ"  ,
        "da" ,"だ"  ,"di" ,"ぢ"  ,"du" ,"づ"  ,"de" ,"で"  ,"do" ,"ど"  ,
        "ba" ,"ば"  ,"bi" ,"び"  ,"bu" ,"ぶ"  ,"be" ,"べ"  ,"bo" ,"ぼ"  ,
        "pa" ,"ぱ"  ,"pi" ,"ぴ"  ,"pu" ,"ぷ"  ,"pe" ,"ぺ"  ,"po" ,"ぽ"  ,
        "ta" ,"た"  ,"ti" ,"てぃ","tu" ,"とぅ","te" ,"て"  ,"to" ,"と"  ,
        "n" ,"ん"  ,"-"  ,"ー"  ,"xtu","っ"  ,
        "xya","ゃ"  ,"xyu","ゅ"  ,"xyo","ょ"  ,
        "xa" ,"ぁ"  ,"xi" ,"ぃ"  ,"xu" ,"ぅ"  ,"xe" ,"ぇ"  ,"xo" ,"ぉ"  ,
                "","", };

bool  isconsonant(char c)
{
static  char  ctab[]="kstnhmyrwzjpbcgf";
  int i;
  for(i=0;ctab[i]!='\0';i++) {
    if (c==ctab[i])
      return(true);
    }
  return(false);
}

bool  isutf8vow(char *s) {
static  char  *utf8vow[]={"あ","い","う","え","お","", };
  for(int i=0;strlen(utf8vow[i])!=0;i++) {
    if (strncmp(utf8vow[i],s,strlen(utf8vow[i]))==0)
      return true;
    }
  return false;
}

bool  isvowel(char c)
{
static  char  vtab[]="aiueo";
  int i;
  for(i=0;vtab[i]!='\0';i++) {
    if (c==vtab[i])
      return(true);
    }
  return(false);
}

void  romaji2kana(char *s,char *o) {
    int idx;
    bool  f;
    while(*s!='\0') {
      idx=0;
      if (isconsonant(*s) && (*s==*(s+1))) { // っの処理
        s++;
        strcpy(o,"っ");
        o+=strlen("っ");
        continue;
        }

      if (*s=='n') { // 'n'の処理
        if ((*(s+1)=='\0')||(*(s+1)=='\n')) { // 次に行末
          strcpy(o,"ん");
          o+=strlen("ん");
          s++;
          continue;
          }
        if (*(s+1)=='-') { // 次に長音
          strcpy(o,"ん");
          o+=strlen("ん");
          s++;
          continue;
          }
        }
        
      f=false;
      while(strlen(tab[idx])!=0) {
        if (strncmp(tab[idx],s,strlen(tab[idx]))==0) {
          // match
          strcpy(o,tab[idx+1]);
          o+=strlen(tab[idx+1]);
          s+=strlen(tab[idx]);
          f= true;
          break;
        }
      idx+=2;
      }
    if (!f) s++;
    }
    *o='\0';
    return;
}

void  kana2romaji(char *s,char *o) {
    int   idx;
    bool  f;
    char  *p=o;
    
    while(*s!='\0') {
    f=false;
    idx=0;
    if (strncmp("ん",s,strlen("ん"))==0) { // んの処理
      char  *t=s+strlen("ん");
      if (isutf8vow(t)) {
        *o='n',*(o+1)='\'';
        o+=2;
        s=t;
        f=true;
        }
      }
    while(strlen(tab[idx])!=0) {
      if (strncmp(tab[idx+1],s,strlen(tab[idx+1]))==0) {
        // match
          strcpy(o,tab[idx]);
          o+=strlen(tab[idx]);
          s+=strlen(tab[idx+1]);
          f=true;
          break;
          }
      idx+=2;
      }
    if (!f) s++;
    }
    *o='\0';

    while(*p) {
      char  c;
      if (strncmp(p,"xtu",3)==0) { // っの処理
        c=*(p+3);
        if (isconsonant(c)) { // 子音
          *p=c;
          strcpy(p+1,p+3);
          }
        else
          break;
        }
      p++;
      }
    return;
}
        
int sl(char *s,char *o) {
    if (isalpha(*s))
      romaji2kana(s,o);
    else
      kana2romaji(s,o);
}

int main(int argc,char *argv[]) {
  char    word[1024];

  if (argc!=2) {
    fprintf(stderr,"Usage (1): %s ことば\n",argv[0]);
    fprintf(stderr,"Usage (2): %s kotoba\n",argv[0]);
    exit(1);
    }

  sl(argv[1],word);
  printf("%s\n",word);
  
  exit(0);
}
