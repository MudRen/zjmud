// Room: /d/xiakedao/xkroad2.c ��ɽ
inherit ROOM;

void create()
{
	set("short", "��ɽ");
	set("long", @LONG
��ɽ�����Ϸ����������н־��������ϸ��ö���
LONG );
	set("outdoors", "xiakedao");
	set("exits", ([
		"north"   : __DIR__"xkroad1",
		"south"   : __DIR__"xkroad3",
	]));
	set("no_clean_up", 0);
	setup();
}
