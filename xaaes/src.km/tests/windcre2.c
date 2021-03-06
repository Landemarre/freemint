#include "aestests.h"


static OBJECT o = {
	-1, -1, -1,
	G_BOX,
	OF_NONE,
	OS_NORMAL,
	{ 0 },
	0, 0, 0, 0
};

static void redraw(GRECT * g)
{
	o.ob_x = g->g_x;
	o.ob_y = g->g_y;
	o.ob_width = g->g_w;
	o.ob_height = g->g_h;
	objc_draw(&o, 0, 0, 0, 0, 0, 0);
}

int main(void)
{
	_WORD hdl;
	_WORD message[8];
	GRECT g;

	appl_init();
	hdl = wind_create(NAME | CLOSER | MOVER, 0, 0, 100, 100);
	if (hdl <= 0)
		return 1;
/*
	wind_set(hdl, WF_NAME, "");
*/
	wind_open(hdl, 50, 50, 100, 100);
	for (;;)
	{
		evnt_mesag(message);
		if (message[0] == WM_CLOSED || message[0] == AP_TERM)
		{
			break;
		} else if (message[0] == WM_TOPPED)
		{
			wind_set(hdl, WF_TOP, 0, 0, 0, 0);
		} else if (message[0] == WM_REDRAW)
		{
			redraw((GRECT *) (message + 4));
		} else if (message[0] == WM_MOVED)
		{
			wind_get(hdl, WF_CURRXYWH, &g.g_x, &g.g_y, &g.g_w, &g.g_h);
			g.g_x = message[4];
			g.g_y = message[5];
			wind_set(hdl, WF_CURRXYWH, g.g_x, g.g_y, g.g_w, g.g_h);
		} else if (message[0] == WM_SIZED)
		{
			wind_get(hdl, WF_CURRXYWH, &g.g_x, &g.g_y, &g.g_w, &g.g_h);
			g.g_w = message[6];
			g.g_h = message[7];
			wind_set(hdl, WF_CURRXYWH, g.g_x, g.g_y, g.g_w, g.g_h);
		}
	}
	
	return 0;
}
