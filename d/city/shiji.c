// Room: /city/zahuopu.c
inherit ROOM;

void create()
{
	set("short", "�м�");
	set("long", @LONG
����һ�㳡�������µ��м�������С�������һ�أ�����һЩ������Ʒ����ֵĻ���������������������£������Ź������ˡ���˵˽������Ҳ��һЩ��
�س��̯������һ������(zhaopai)��
LONG );
	set("item_desc", ([
		"zhaopai": "ֻ����Ե��\n",
	]));
	set("no_fight",1);
	set("exits", ([
		"up" :  __DIR__"level_up",
		"down" : __DIR__"guangchang",
		
	]));
	set("objects", ([
		"adm/npc/beastseller": 1,
	]));
	setup();
}

