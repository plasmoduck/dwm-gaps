/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "Wuncon Siji:size=12", "xos4 Terminus:size=9:antialias=true:autohint=true" };

static const char dmenufont[]       = "xos4 Terminus:size=10";

#include "/home/cjg/themes/vader/colors-wal-dwm.h"

/* tagging */
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */
static const char *tags[] = {  "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask    iscentered	 isfloating   monitor */
        { "Gimp",     NULL,       NULL,       1 << 5,      0,	 	 0,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 3,      0, 	 	 0,           -1 },
        { "thunderbird", NULL,    NULL,       1 << 4,      0, 	 	 0,           -1 },
        { "Pcmanfm",   NULL,      NULL,       1 << 4,      0, 	 	 0,           -1 },
        { "Hexchat",  NULL,       NULL,       1 << 5,      0, 	 	 0,           -1 },
        { "Telegram",   NULL,     NULL,       1 << 5,      0, 	 	 0,           -1 },
        { "Code - OSS", NULL,     NULL,       1 << 4,      0, 	 	 0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
	{ "",      spiral },
	{ "",      dwindle },
	{ "",      centeredmaster },
	{ "",      centeredfloatingmaster },

	{ "",                tcl },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "20", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *browser[] = { "firefox", NULL};
static const char *xmixer[] = { "xmixer", NULL };
static const char *hexchat[] = { "hexchat", NULL };
static const char *files[] = { "thunar", NULL };
static const char *upvol[]   = { "mixer", "vol", "+3",     NULL };
static const char *downvol[] = { "mixer", "vol", "-3",     NULL };
static const char *mutevol[] = { "mixer", "vol", "toggle", NULL };
static const char *gimp[] = { "gimp", NULL };
static const char *scrot[] = { "scrot", "/home/cjg/pictures/scrot.png", NULL };
static const char *vbox[] = { "doas", "VirtualBox", NULL };
static const char *email[] = { "thunderbird", NULL };
static const char *mpcnxt[] = { "mpc", "-h", "/usr/home/cjg/.mpd/socket", "next", NULL};
static const char *mpctgl[] = { "mpc", "-h", "/usr/home/cjg/.mpd/socket", "toggle", NULL};
static const char *mpcstp[] = { "mpc", "-h", "/usr/home/cjg/.mpd/socket", "stop", NULL};
static const char *mpcprv[] = { "mpc", "-h", "/usr/home/cjg/.mpd/socket", "prev", NULL};
static const char *slock[] = { "slock", NULL};
static const char *theme[] = { "theme", NULL};
static const char *reboot[] = { "doas", "reboot", NULL};

#include "selfrestart.c"
#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_s,      spawn,          {.v = browser } },
  { MODKEY,                       XK_e,      spawn,          {.v = email } },
  { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = gimp } },
  { MODKEY|ShiftMask,             XK_r,	     spawn,	         {.v = reboot } },
	{ MODKEY,                       XK_t,	     spawn,	         {.v = theme } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vbox } },
  { MODKEY,                       XK_x,      spawn,          {.v = hexchat } },
  { MODKEY,                       XK_f,      spawn,          {.v = files } },
  { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scrot } },
  { MODKEY|ShiftMask,            	XK_End,	   spawn,	         {.v = slock } },
	{ MODKEY,                       XK_F12,    spawn,          {.v = mpcnxt } },
  { MODKEY,                       XK_F9,     spawn,          {.v = mpctgl } },
  { MODKEY,                       XK_F10,	   spawn,	   {.v = mpcstp } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = mpcprv } },
	{ MODKEY,                       XK_Pause,  spawn,          {.v = upvol   } },
	{ MODKEY,              	        XK_Scroll_Lock,    spawn,  {.v = downvol } },
  { MODKEY,     	                XK_Print,  spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_t,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,	            XK_d,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		          XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,  		      XK_r,      self_restart,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

