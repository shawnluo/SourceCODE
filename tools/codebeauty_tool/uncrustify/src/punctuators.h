/**
 * @file punctuators.h
 * Automatically generated
 */
static const lookup_entry_t punc_table[] =
{
   { '!', 26, 27, &symbols1[0]  },   //   0: '!'
   { '#', 25, 36, &symbols1[1]  },   //   1: '#'
   { '$', 24,  0, &symbols1[2]  },   //   2: '$'
   { '%', 23, 38, &symbols1[3]  },   //   3: '%'
   { '&', 22, 43, &symbols1[4]  },   //   4: '&'
   { '(', 21,  0, &symbols1[5]  },   //   5: '('
   { ')', 20,  0, &symbols1[6]  },   //   6: ')'
   { '*', 19, 45, &symbols1[7]  },   //   7: '*'
   { '+', 18, 46, &symbols1[8]  },   //   8: '+'
   { ',', 17,  0, &symbols1[9]  },   //   9: ','
   { '-', 16, 48, &symbols1[10] },   //  10: '-'
   { '.', 15, 52, &symbols1[11] },   //  11: '.'
   { '/', 14, 55, &symbols1[12] },   //  12: '/'
   { ':', 13, 56, &symbols1[13] },   //  13: ':'
   { ';', 12,  0, &symbols1[14] },   //  14: ';'
   { '<', 11, 58, &symbols1[15] },   //  15: '<'
   { '=', 10, 65, &symbols1[16] },   //  16: '='
   { '>',  9, 68, &symbols1[17] },   //  17: '>'
   { '?',  8, 73, &symbols1[19] },   //  18: '?'
   { '@',  7,  0, &symbols1[18] },   //  19: '@'
   { '[',  6, 75, &symbols1[20] },   //  20: '['
   { ']',  5,  0, &symbols1[21] },   //  21: ']'
   { '^',  4, 76, &symbols1[22] },   //  22: '^'
   { '{',  3,  0, &symbols1[23] },   //  23: '{'
   { '|',  2, 77, &symbols1[24] },   //  24: '|'
   { '}',  1,  0, &symbols1[25] },   //  25: '}'
   { '~',  0, 79, &symbols1[26] },   //  26: '~'
   { '<',  3, 31, &symbols2[0]  },   //  27: '!<'
   { '=',  2, 34, &symbols2[1]  },   //  28: '!='
   { '>',  1, 35, &symbols2[2]  },   //  29: '!>'
   { '~',  0,  0, &symbols2[3]  },   //  30: '!~'
   { '=',  1,  0, &symbols3[0]  },   //  31: '!<='
   { '>',  0, 33, &symbols3[1]  },   //  32: '!<>'
   { '=',  0,  0, &symbols4[0]  },   //  33: '!<>='
   { '=',  0,  0, &symbols3[2]  },   //  34: '!=='
   { '=',  0,  0, &symbols3[3]  },   //  35: '!>='
   { '#',  1,  0, &symbols2[4]  },   //  36: '##'
   { '@',  0,  0, &symbols2[5]  },   //  37: '#@'
   { ':',  2, 41, &symbols2[38] },   //  38: '%:'
   { '=',  1,  0, &symbols2[6]  },   //  39: '%='
   { '>',  0,  0, &symbols2[35] },   //  40: '%>'
   { '%',  0, 42, NULL          },   //  41: '%:%'
   { ':',  0,  0, &symbols4[2]  },   //  42: '%:%:'
   { '&',  1,  0, &symbols2[7]  },   //  43: '&&'
   { '=',  0,  0, &symbols2[8]  },   //  44: '&='
   { '=',  0,  0, &symbols2[9]  },   //  45: '*='
   { '+',  1,  0, &symbols2[10] },   //  46: '++'
   { '=',  0,  0, &symbols2[11] },   //  47: '+='
   { '-',  2,  0, &symbols2[12] },   //  48: '--'
   { '=',  1,  0, &symbols2[13] },   //  49: '-='
   { '>',  0, 51, &symbols2[14] },   //  50: '->'
   { '*',  0,  0, &symbols3[4]  },   //  51: '->*'
   { '*',  1,  0, &symbols2[15] },   //  52: '.*'
   { '.',  0, 54, &symbols2[16] },   //  53: '..'
   { '.',  0,  0, &symbols3[5]  },   //  54: '...'
   { '=',  0,  0, &symbols2[18] },   //  55: '/='
   { ':',  1,  0, &symbols2[19] },   //  56: '::'
   { '>',  0,  0, &symbols2[37] },   //  57: ':>'
   { '%',  4,  0, &symbols2[34] },   //  58: '<%'
   { ':',  3,  0, &symbols2[36] },   //  59: '<:'
   { '<',  2, 63, &symbols2[20] },   //  60: '<<'
   { '=',  1,  0, &symbols2[21] },   //  61: '<='
   { '>',  0, 64, &symbols2[22] },   //  62: '<>'
   { '=',  0,  0, &symbols3[6]  },   //  63: '<<='
   { '=',  0,  0, &symbols3[7]  },   //  64: '<>='
   { '=',  1, 67, &symbols2[23] },   //  65: '=='
   { '>',  0,  0, &symbols2[32] },   //  66: '=>'
   { '=',  0,  0, &symbols3[8]  },   //  67: '==='
   { '=',  1,  0, &symbols2[24] },   //  68: '>='
   { '>',  0, 70, &symbols2[25] },   //  69: '>>'
   { '=',  1,  0, &symbols3[9]  },   //  70: '>>='
   { '>',  0, 72, &symbols3[10] },   //  71: '>>>'
   { '=',  0,  0, &symbols4[1]  },   //  72: '>>>='
   { '.',  1,  0, &symbols2[17] },   //  73: '?.'
   { '?',  0,  0, &symbols2[33] },   //  74: '??'
   { ']',  0,  0, &symbols2[26] },   //  75: '[]'
   { '=',  0,  0, &symbols2[27] },   //  76: '^='
   { '=',  1,  0, &symbols2[28] },   //  77: '|='
   { '|',  0,  0, &symbols2[29] },   //  78: '||'
   { '=',  1,  0, &symbols2[30] },   //  79: '~='
   { '~',  0,  0, &symbols2[31] },   //  80: '~~'
};
