// Room: /city/zahuopu.c

inherit ROOM;

void create()
{
	set("short", "�ӻ���");
	set("long", @LONG
����һ��СС���ӻ��̣�����С�������һ�أ�����һЩ�ճ���Ʒ����
�ƹ������������һֻ�����ϣ��к��Ź������ˡ���˵˽������Ҳ��һЩ��
�صĶ�����̯������һ������(zhaopai)��
LONG );

	set("exits", ([
		"north" : __DIR__"dongdajie1",
		"south" : __DIR__"zahuo_neishi",
		"up"    : __DIR__"garments",
		
	]));
	set("objects", ([
		__DIR__"npc/yang": 1,
	]));
	setup();
}

