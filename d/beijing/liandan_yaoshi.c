// liandan_yaoshi.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "Ҧ������");
	set("long", @LONG
������һ��СС�ķ��䣬ûʲô�ر�ĵط����㿴�������Ա���һλͷ��
���׵����������Ķ����飬�Ǳ��Ǿ��ǻش��������ġ�������ҽ��Ҧ���ˡ�Ҧ
����ǰ����һ�Ȱ뿪�����ţ���ͣ�Ĵ�����ð������Ũ�ҵ�ҩζ.
LONG );
	//set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/liandan_yaochun" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"liandan_fang",
		"south": __DIR__"liandan_neiting",
	]));

	setup();
}

