// Room: /d/fuzhou/nanmen.c
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����Ǹ������ţ��ƺ�ûʲô��������Ҳû�йٱ���������ء�
LONG );
	set("exits", ([
		"south" : __DIR__"zhongzhou",
		"north" : __DIR__"nanmendou",
	]));
	set("outdoors", "fuzhou");
	setup();
}

