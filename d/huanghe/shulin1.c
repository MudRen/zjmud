// Room: /huanghe/shulin1.c
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
��������߰�����ֻ������ͷ���ϴ���һЩ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ�����ᴫ��Ұ
�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ�����������һ�����ӡ�
LONG );
	set("exits", ([
		"west"  : __DIR__"shulin2",
		"east"  : __DIR__"caodi2",
		"north" : __DIR__"shulin3",
	]));
	set("item_desc", ([
		"�����ӡ�" : HIR"\n�ǻƺӰ�����    �����ɱ����"NOR"\n",
	]));
	set("objects", ([
		"/clone/beast/dushe" : 1,
		"/d/hangzhou/obj/shuzhi" : 1,
	]));

	set("resource/snake", ({ "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe", }));

	set("outdoors", "huanghe");
	setup();
}
