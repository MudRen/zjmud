// wuchang.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
����һ���������䳡���м�����ִ�̽���������Ů������������
�Ա�վ�ż��ˣ�������Ů��������ֻ�ж���ʮ�꣬�ϵ���������ʮ
�꣬����ȴ�������С����ߡ��ϱ���һƬ��������䳡��������ͨ��
һ�����ȡ�
LONG );
	set("exits", ([
		"north" : __DIR__"zoulang",
		"south" : __DIR__"wuchang2",
		"east"  : __DIR__"wuchang3",
	]));
	set("objects", ([
		"/clone/npc/mu-ren": 3,
	]));
	set("for_family", "������");
	setup();
}
