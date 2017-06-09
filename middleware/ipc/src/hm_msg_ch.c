#include "main.h"
#include "hm_msg_ch.h"
#include "hm_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"

#define MAX_CH_NAME_LEN 16u
#define MAX_NUM_CH 2u

struct hm_msg_ch_t {
    char name[MAX_CH_NAME_LEN];
    uint8_t is_alloc;
    QueueHandle_t xQ;
};

QueueHandle_t xQ;

static hm_msg_ch_t hm_msg_ch_pool[MAX_CH_NAME_LEN];

hm_msg_ch_t *hm_msg_ch_init(char *ch_name, uint32_t len)
{
    uint32_t i;

    for (i = 0; i < MAX_NUM_CH; i++){
        if (hm_msg_ch_pool[i].is_alloc)
            continue;
    
        //hm_msg_ch_pool[i].xQ =  xQueueCreate(len, sizeof(msg_t *));
        xQ =  xQueueCreate(len, sizeof(msg_t *));
        hm_msg_ch_pool[i].is_alloc = 1;
        strcpy(hm_msg_ch_pool[i].name, ch_name);

        return &hm_msg_ch_pool[i];
    }

    return NULL;
}

void hm_msg_ch_deinit(hm_msg_ch_t *ch)
{
    ch->is_alloc = 0;
    ch->name[0] = '\0'; 
}

hm_msg_ch_t *hm_msg_ch_attach(char *ch_name)
{
    uint32_t i;

    for (i = 0; i < MAX_NUM_CH; i++){        
        if (!strcmp(ch_name, hm_msg_ch_pool[i].name)){
           return  &hm_msg_ch_pool[i];
        }
    }

    return NULL;
}

void hm_msg_ch_deattach(hm_msg_ch_t *ch)
{

}

uint32_t hm_msg_ch_send(hm_msg_ch_t *ch, msg_t *m)
{
    return xQueueSend(ch->xQ, m, portMAX_DELAY);
}

uint32_t hm_msg_ch_recv(hm_msg_ch_t *ch, msg_t *m)
{
    return xQueueReceive(ch->xQ, m, portMAX_DELAY);
}
