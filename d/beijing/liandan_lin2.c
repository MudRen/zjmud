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
		"north" : __DIR__"ximenwai",
		"south" : __DIR__"liandan_lin6",
		"east" : __DIR__"liandan_lin7",
		"west" : __DIR__"liandan_lin8",
	]));

	setup();
	replace_program(LIANDAN_LIN);
}
