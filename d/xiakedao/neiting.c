// neiting.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ��ʯ�����˶�˶���������ܵ����˻�ѣ�������������
ҫ��ʮ���������м���źܶ�ʯ����ʯ�ʣ��кܶ�Ľ���������ʯ��
�ڲ����书֮�࣬��������Ϣһ�ᡣ
LONG );

	set("exits", ([
		"enter" : __DIR__"shihole1",
		"north" : __DIR__"xiuxis2",
		"east"  : __DIR__"shibi",
		"west"  : __DIR__"chashi",
	]));

	set("objects", ([
		__DIR__"npc/shipotian" : 1,
		__DIR__"npc/daoseng": 1,
		__DIR__"npc/dizi": 2,
	]));

	setup();
}
