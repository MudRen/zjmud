// Room: /city/dangpu.c
inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
����һ����������ƽ���Ƶĵ��̣�һ����߸ߵĹ�̨���������
ǰ����̨�ϰ���һ������(paizi)�� ��̨���������ϰ壬һ˫������
�������´������㡣
LONG
	);
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("item_desc", ([
		"�����ӡ�" : "��ƽ����\n
sell	�� 
buy	 ��
redeem      ��
value       ����
",
	]));
/*
	set("objects", ([
		__DIR__"npc/tang" : 1,
	]));
*/
	set("exits", ([
		"west" : __DIR__"nandajie1",
		"down" : __DIR__"xsmidao",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "down" && me->query("family/family_name") != "ѩɽ��")
		return notify_fail("����۾�һ����������ʲô���ˣ���͵��������\n");

	return ::valid_leave(me, dir);
}
