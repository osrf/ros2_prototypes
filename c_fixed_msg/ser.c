#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
  char *bill;
  char *ted;
} excellent_t;

static const uint32_t EXCELLENT_10_10_BILL_MAXLEN = 10;
static const uint32_t EXCELLENT_10_10_TED_MAXLEN  = 10;
typedef struct
{
  char bill[10];
  char ted[10];
} excellent_10_10_t;

#define BE_EXCELLENT(bill_len, ted_len) \
  static const uint32_t EXCELLENT_##bill_len##_##ted_len##_BILL_MAXLEN = bill_len; \
  static const uint32_t EXCELLENT_##bill_len##_##ted_len##_TED_MAXLEN  = ted_len; \
  typedef struct { \
    char bill[bill_len]; \
    char ted[ted_len]; \
  } excellent_##bill_len##_##ted_len##_t; \
  void excellent_##bill_len##_##ted_len##_deserialize (const excellent_t *in, excellent_##bill_len##_##ted_len##_t *out) \
  { \
    str_chop(out->bill, in->bill, EXCELLENT_##bill_len##_##ted_len##_BILL_MAXLEN); \
    str_chop(out->ted, in->ted, EXCELLENT_##bill_len##_##ted_len##_TED_MAXLEN); \
  }

void str_chop(char *out, const char *in, const uint32_t out_maxlen)
{
  const char *c = in;
  char *d = out;
  for (; *c && (d - out < out_maxlen - 1); c++, d++)
    *d = *c;
  *d = 0;
}

void rx_excellent_10_10(const excellent_t *in, excellent_10_10_t *out)
{
  str_chop(out->bill, in->bill, EXCELLENT_10_10_BILL_MAXLEN);
  str_chop(out->ted, in->ted, EXCELLENT_10_10_TED_MAXLEN);
}

BE_EXCELLENT(9,9);
BE_EXCELLENT(8,2);
BE_EXCELLENT(30,4);

int main(int argc, char **argv)
{
  printf("hello, world!\r\n");
  excellent_t in = { "wooooooahhhhhhhhhh", "wooowwwwwwwww" };
  excellent_10_10_t out;
  rx_excellent_10_10(&in, &out);
  printf("[%s], [%s]  --> [%s] [%s]\n", in.bill, in.ted, out.bill, out.ted);

  excellent_9_9_t out2;
  excellent_9_9_deserialize(&in, &out2);
  printf("[%s], [%s]  --> [%s] [%s]\n", in.bill, in.ted, out2.bill, out2.ted);

  excellent_8_2_t out3;
  excellent_8_2_deserialize(&in, &out3);
  printf("[%s], [%s]  --> [%s] [%s]\n", in.bill, in.ted, out3.bill, out3.ted);

  excellent_30_4_t out4;
  excellent_30_4_deserialize(&in, &out4);
  printf("[%s], [%s]  --> [%s] [%s]\n", in.bill, in.ted, out4.bill, out4.ted);

  return 0;
}

