// Room: /d/xiakedao/xkroad6.c
inherit ROOM;

void create()
{
	set("short", "���С��");
	set("long", @LONG
С�������С��ʮ�ּ�ª������ûʲô�ҵ������Ϲ��������þ�
�˵���ߡ���Ŵ��˶������ˣ�ֻ��һ��С����������������һ
�����̡�
LONG );
	set("exits", ([
		"south"   : __DIR__"xkroad5",
	]));
	set("objects", ([
		__DIR__"npc/kid": 1,
	]));
	setup();
}

