#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","��������");
	set("long", @LONG
���������ݸ������ң����������ƺ�Ҳû�����ʲô�ر�ı�����
LONG );
	set("exits", ([
		"up" :  __DIR__"aofu_shufang",
	]));

	"/clone/weapon/xtbishou"->foo();
	"/clone/weapon/jsbaojia"->foo();

	setup();
}
