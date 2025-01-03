/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:size=10";
// colors from https://github.com/thamognya/DWM-Nord-Theme/tree/master //
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char nord_polar_darkest_blue[]        = "#2E3440";
static const char nord_polar_darker_blue[]        = "#3B4252";
static const char nord_polar_lighter_dark_blue[]        = "#434C5E";
static const char nord_polar_lightest_dark_blue[]        = "#4C566A";
static const char nord_dark_white[]        = "#D8DEE9";
static const char nord_darker_white[]        = "#E5E9F0";
static const char nord_white[]        = "#ECEFF4";
static const char nord_white_dark[]        = "#d8dee9";
static const char nord_frost_light_blue[]        = "#8FBCBB";
static const char nord_frost_darker_light_blue[]        = "#88C0D0";
static const char nord_frost_lighter_dark_blue[]        = "#81A1C1";
static const char nord_frost_dark_blue[]        = "#5E81AC";
static const char nord_red[]        = "#BF616A";
static const char nord_orange[]        = "#D08770";
static const char nord_yellow[]        = "#EBCB8B";
static const char nord_green[]        = "#A3BE8C";
static const char nord_purple[]        = "#B48EAD";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { nord_white, nord_polar_darkest_blue, nord_polar_darkest_blue },
	[SchemeSel]  = { nord_polar_darkest_blue, nord_frost_darker_light_blue,  nord_red },

//    [SchemeTabActive]  = { nord_polar_darkest_blue, nord_polar_darkest_blue,  nord_red },
//    [SchemeTabInactive]  = { nord_white, nord_polar_darkest_blue,  nord_polar_darkest_blue }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "thunderbird-default",     "Alert",       NULL,       0,            1,           -1 },
	{ "Mumble",     NULL,       NULL,       0,            1,           -1 },
	{ "guvcview",     NULL,       NULL,       0,            1,           -1 },
	{ "Guvcview",     NULL,       NULL,       0,            1,           -1 },
	{ "simplescreenrecorder",     NULL,       NULL,       0,            1,           -1 },
	{ "SimpleScreenRecorder",     NULL,       NULL,       0,            1,           -1 },
	
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* autostart array from cool autostart patch */
// static const char *const autostart[] = {
//		"bash", "/home/corey/start-thinkpad.sh", NULL,
//		NULL
// };


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|M|",      centeredmaster }, /* first entry is default */
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ ">M>",      centeredfloatingmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/* Corey's custom commands */
static const char *firefox[] = { "firefox", NULL};
static const char *thunderbird[] = { "thunderbird", NULL};
static const char *pcmanfmqt[] = { "pcmanfm-qt", NULL};
static const char *zotero[] = { "zotero", NULL};
static const char *texmaker[] = { "texmaker", NULL};
static const char *lxqtleave[] = { "lxqt-leave", NULL};
/* ThinkPad Media Controls */
static const char *upvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
/* ThinkPad Brightness Controls */
/* To use light add this to the constant definition section. Thanks Hritik14. */
static const char *light_up[]   = { "sudo", "/usr/bin/light",   "-A", "5", NULL };
static const char *light_down[] = { "sudo", "/usr/bin/light",   "-U", "5", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
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
// Corey's custom launchers
	{ MODKEY|ShiftMask,             XK_f, 		spawn,   		{.v = firefox } },
	{ MODKEY|ShiftMask,             XK_t, 		spawn,   		{.v = thunderbird } },
	{ MODKEY|ShiftMask,             XK_p, 		spawn,   		{.v = pcmanfmqt } },
	{ MODKEY|ShiftMask,             XK_z, 		spawn,   		{.v = zotero } },
	{ MODKEY|ShiftMask,             XK_m, 		spawn,   		{.v = texmaker } },
	{ MODKEY|ShiftMask,             XK_x, 		spawn,   		{.v = lxqtleave } },
// ThinkPad Media Keys
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
// ThinkPad Brightness Keys
	{ 0,				XF86XK_MonBrightnessUp,		spawn,	{.v = light_up} },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,	{.v = light_down} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

