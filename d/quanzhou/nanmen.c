// Room: /d/quanzhou/nanmen.c
inherit ROOM;

void create()
{
	set("short", "Ȫ������");
	set("long", @LONG
�������Ϸ���һ��Ȫ�ݵ����š���������һƬ��Ұ��
LONG );
	set("exits", ([
		"north" : __DIR__"zhongxin",
	]));
	set("no_clean_up", 0);
	set("outdoors", "quanzhou");
	setup();
}

