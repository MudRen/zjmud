// liandan_lin7.c

#include <ansi.h> 

#define LIANDAN_LIN     __DIR__"liandan_lin"

inherit LIANDAN_LIN;

void create()
{
	set("short", "��������");
	set("long", @LONG
����һƬï�ܵ����֡��ܶ�ü�ʮ�ɸߵĴ�������һ�飬��һ�Ѱ������
ɡ�������¶����ڱεð�Ȼ�޹⡣�����л���ʱ������������Ȼ���������졣
LONG );
	set("exits", ([
		"east" : __DIR__"liandan_lin1",
	]));

	set("objects", ([
		"/clone/npc/walker" : 1,
	]));

	setup();
	replace_program(LIANDAN_LIN);
}
