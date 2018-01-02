#ifndef __HM_BROKER_H__
#define __HM_BROKER_H__
#include "gen_types.h"

#define MAX_PLD_LEN 6u

typedef struct {
	uint16_t type;
	uint8_t pld[MAX_PLD_LEN];
} hm_msg_t;
#endif /* __HM_MSG_CH_H__ */
