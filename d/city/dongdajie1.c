// Room: /city/dongdajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ��ֵ������߲�ʱ�ش�������ײ
�����������������ӡ�������һ�����ӵ�Ժ�ӣ������Ϸ�д�š���
¹��Ժ���ĸ��̽���֡��ϱ���һ���ӻ��̡�
LONG );
	set("outdoors", "city");
	set("exits", ([
		"east" : __DIR__"dongdajie2",
		"south" : __DIR__"zahuopu",
		"west" : __DIR__"guangchang",
		"north" : __DIR__"shuyuan",
	]));

	set("objects", ([
		"/clone/npc/xunbu" : 1,
	]));
	setup();
}

