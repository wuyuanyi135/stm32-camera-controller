#include <usbd_cdc_if.h>
#include "task_monitor.h"
#include "pt_util.h"
#include "usbd_cdc_extension.h"
#include "led_status.h"
#include "usbd_def.h"
#include "usb_device.h"

#define PERSISTED(NEW, OLD, EXEC) if (NEW != OLD) {EXEC;OLD = NEW;}

uint32_t strobing_sequence[] =
{ 200, 200, 400, 200, 1000, 200 };

void update_cdc_state ()
{
	if (CDC_Transmit_FS(NULL, 0) == USBD_OK)
	{
		usbd_cdc_ext_dtr = 1;
	}
	else
	{
		usbd_cdc_ext_dtr = 0;
	}
}
PT_THREAD(task_monitor_cdc_connection(struct pt* pt))
{
	static uint8_t old_cdc_state, old_dev_state;
	PT_BEGIN(pt);
		old_cdc_state = 0xff;	// some impossible value to ensure the execution
		old_dev_state = USBD_STATE_DEFAULT;
		while (1)
		{
			if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED)
			{
				// check whether cdc is open
				update_cdc_state();

				if (usbd_cdc_ext_dtr)
				{
					// cdc connected
					PERSISTED(usbd_cdc_ext_dtr, old_cdc_state, led_always(LED_ON));
				}
				else
				{
					// cdc not yet connected
					PERSISTED(usbd_cdc_ext_dtr, old_cdc_state,
							led_strobe(strobing_sequence,
									sizeof(strobing_sequence)
											/ sizeof(uint32_t), 0));
				}

			}
			else
			{
				// usb not connected
				// prevent repeat execution
				PERSISTED(hUsbDeviceFS.dev_state, old_dev_state, led_always(LED_OFF));
			}

			PT_TIME_DELAY_TICK(pt, TASK_MONITOR_POLL_INTERVAL);
		}
	PT_END(pt)
;
}
