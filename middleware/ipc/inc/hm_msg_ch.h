#ifndef __HM_MSG_CH_H__
#define __HM_MSG_CH_H__
#include "main.h"

typedef struct hm_msg_ch_t hm_msg_ch_t;

typedef uint32_t msg_t;

hm_msg_ch_t* hm_msg_ch_init(char *ch_name, uint8_t len);
void hm_msg_ch_deinit(hm_msg_ch_t *ch);

hm_msg_ch_t* hm_msg_ch_attach(char *ch_name);
void hm_msg_ch_deattach(hm_msg_ch_t *ch);

uint32_t hm_msg_ch_send(hm_msg_ch_t *ch, msg_t *m);
uint32_t hm_msg_ch_recv(hm_msg_ch_t *ch, msg_t *m);

#endif /* __HM_MSG_CH_H__ */
