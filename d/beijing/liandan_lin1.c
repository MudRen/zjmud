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
		"south" : __DIR__"ximenwai",
		//"north" : __DIR__"liandan_lin3",
		//"east" : __DIR__"liandan_lin5",
		//"west" : __DIR__"liandan_lin4",
	]));

	setup();
	replace_program(LIANDAN_LIN);
}
