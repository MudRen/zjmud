// Room: /d/fuzhou/kedian.c
inherit ROOM;
void create()
{
	set("short", "�͵�");
	set("long", @LONG
ɽҰ�͵�ʮ�ּ�ª��һ��С����̨������һƬ���������ڵ�
�ϣ��Ե��൱æ�ҡ���̨�����Ÿ����ӡ�
LONG );
	set("exits", ([
		"east" : __DIR__"erbapu",
	]));
	set("item_desc", ([
		"�����ӡ�" : "������ֻ��Ӧ�Ժȣ������ޡ�\n",
	]));
	set("valid_startroom", 1);
	set("no_sleep_room", 1);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/xiaoer2" : 1,
	]));
	setup();
}

