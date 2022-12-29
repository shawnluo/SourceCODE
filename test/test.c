#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char *reverse_s(char *s, int start, int end) {
    int left = 0;
    int size = strlen(s);
    int right = size - 1;
    while(left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
    }

    return NULL;
}


char *replace_s(char *s, int size) {
    int flag = 0;
    for(int i = 0; i < size; i++) {
        if((i > flag * 1000) && (i < 1000 * (flag + 1))) {
            reverse_s(s, flag * 1000, size - flag * 1000);
        }
    }
    return NULL;
}


//the elements in s are uniq
int isUniq(char *s, int L, int R) {
    for(int i = L; i < R - 1; i++) {
        for(int j = i + 1; j < R; j++) {
            if(s[i] == s[j]) {
                return 0;
            }
        }
    }
    return 1;
}


int long_uniq_sub(char *s) {
    int max = 0;
    int L, R;
    int size = strlen(s);
    char save[size];
    memset(save, 0, size);
    for(R = 1; R < size; R++) {
        for(L = R - 1; L >= 0; L--) {
            //if((s[L] == s[R]) && ((R - L) > max)) {
            int uniq = isUniq(s, L, R);
            //printf("L = %d, R = %d, uniq = %d, max = %d, len = %d\n", L, R, uniq, max, R - L);
            if(!uniq) {
                if(R - L > max) {
                    max = R - L;
                    strncpy(save, s + L + 1, max);
                    save[max] = '\0';
                    printf("save: %s\n", save);
                }
                break;
            }
        }

        //printf("L = %d\n", L);
        if(L == -1) {
            max = R + 1;
            strncpy(save, s, max);
            save[max] = '\0';
            //printf("%s\n", save);
        }
    }

    printf("%s\n", save);
    return max;
}


void longest_common_sub(char *s1, char *s2) {
    int p1, p2;
    int max = 0;
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    char save[100] = {0};

    for(p1 = 0; p1 < size1; p1++) {
        int tmp1 = p1;
        for(p2 = 0; p2 < size2; p2++) {
            int tmp2 = p2;
            while(s1[tmp1] == s2[tmp2]) {
                tmp1++;
                tmp2++;
            }
            if(tmp1 < size1 && tmp2 < size2) {
                if(tmp1 - p1 > max) {
                    max = tmp1 - p1;
                    strncpy(save, s1 + p1, max);
                    printf("-> 1: %d, %d, %d\n", p1, tmp1, max);
                }
                break;
            } else if(tmp1 == size1) {
                if(tmp1 - p1 > max) {
                    max = tmp1 - p1;
                    strncpy(save, s1 + p1, max);
                    printf("-> 2: %d, %d, %d\n", p1, tmp1, max);
                }
            } else if(tmp2 == size2) {
                if(tmp2 - p2 > max) {
                    max = tmp2 - p2;
                    strncpy(save, s2 + p2, max);
                    printf("-> 3: %d, %d, %d\n", p2, tmp2, max);
                }
            }
        }
    }
    printf("%s\n", save);
}
#if 0
void LCS(char *s1, char *s2) {
    int i, j, max = 0;
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    char save[100] = {0};

    int dp[100][100] = {0};

    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if(i == 0 && s1[i] == s2[j]) dp[0][j] = 1;
            if(j == 0 && s1[i] == s2[j]) dp[i][0] = 1;

            if(s1[i] == s2[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
        }
    }

    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    int save_index = 0;
    //find the biggest element
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if(dp[i][j] > max) {
                max = dp[i][j];
                save_index = i;
            }
        }
    }

    printf("save_index = %d\n", save_index);
    while(max > 0) {
        printf("%c ", s1[save_index - max + 1]);
        max--;
    }
    printf("\n");
}
#endif


//longest common substring
void LCS(char *s1, char *s2) {
    /*
        dp[i][j]: the length of the common characters in row
        i, j:     the index element of s1 and s2
        dp[i][j] = s[i] == s[j] ? dp[i - 1][j - 1] + 1 : 0
    */
   int i, j, max = 0;
   int size1 = strlen(s1);
    int size2 = strlen(s2);
    int dp[size1][size2];
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if(s1[0] == s2[j]) {
                dp[0][j] = 1;
            }
            if(s1[i] == s2[0]) {
                dp[i][0] = 1;
            }
            dp[i][j] = s1[i] == s2[j] ? dp[i - 1][j - 1] + 1 : 0;
        }
    }
    //print dp[][]
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}

int max(int x, int y) {
    return x >= y ? x: y;
}

#if 0
int longestSubstring(char *s) {
    //利用哈希的思想,key是每一个字符,value是其对应的下标
    // 存储上一个重复字符的位置
    int lastPosition[256];
    //初始化,首字符之前没有与其重复的字符,都为-1
    for (int i = 0; i < 256; i++) {
        lastPosition[i] = -1;
    }

    int previous = -1;  //记录上一个不重复子串的终点
    int current = 0;    //记录当前不重复子串长度
    int maxLength = 0;  //记录最大不重复子串长度
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        //碰到重复字符previous更改为该重复字符的位置
        previous = max(previous, lastPosition[s[i]]);
        //本次子串长度
        current = i - previous;
        maxLength = max(current, maxLength);
        //更新该字符对应的下标
        lastPosition[s[i]] = i;
    }
    return maxLength;
}
#endif


void longest_common_sub_dp(char *s1, char *s2) {
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    int dp[size1][size2];
    int max = 0;

    for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
            dp[i][j] = 0;
        }
    }

    for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
            if((i == 0 || j == 0) && (s1[i]  == s2[j])) {
                dp[i][j] = 1;
            } else if(s1[i] == s2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                max = dp[i][j] > max ? dp[i][j] : max;
            }
        }
    }

    printf("%d\n", max);
}


int longest_uniq_sub(char *s) {
    int len = 0;
    int max_len = 0;
    int pos = -1;
    int size = strlen(s);
    int hash[256];
    for(int i = 0; i < 256; i++) {
        hash[i] = -1;
    }

    for(int i = 0; i < size; i++) {
        pos = max(pos, hash[s[i]]);
        len = i - pos;
        max_len = max(max_len, len);
        hash[s[i]] = i;
    }

    return max_len;
}


int is_uniq_2(char *s, int left, int right) {
    for(int i = left; i < right; i++) {
        for(int j = i + 1; j < right; j++) {
            if(s[i] == s[j]) return 0;
        }
    }
    return 1;
}


/*  brute force
    from second to the end, checking from pos back to front, are all characters uniq?
*/
#define TRUE 1
#define FALSE 0

void longest_uniq_sub_1(char *s) {
    int size = strlen(s);
    int len = 0;    //the length of unique characters
    int max_len = 0;
    char save[size];
    memset(save, 0, size);
    int i, j;

    for(i = 1; i < size; i++) {
        for(j = i - 1; j >= 0; j--) {
            if(is_uniq_2(s, i, j) == FALSE) {
                len = i - j;
                if(len > max_len) {
                    max_len = len;
                    strncpy(save, s + j + 1, len);
                }
                break;
            }
        }
        if(j == -1) {
            max_len = i + 1;
            printf("%d\n", max_len);
            strncpy(save, s, max_len);
        }
    }
    printf("%s\n", save);
}


int main(int argc, char *argv[]) {
    char s1[] = "abxcaxbcdea";
    char s2[] = "abxcmanxbfc";

    //longest_common_sub_dp(s1, s2);
    //LCS(s1, s2);

    char *s = "aabbcdd";
    longest_uniq_sub_1(s);

    return 0;
}