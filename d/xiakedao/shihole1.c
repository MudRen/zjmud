// /d/xiakedao/shihole1.c ���͵� ʯ��1

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
��������������ʯ��������ͨ���ľ�ʫ��ʯ�ҡ�������ϰ������
�С��书����������ܸ٣�Ҳ�ֱ��������˶�һɫ�಼�ᣣ���
���ĵ��Ӿ������³�����������ϣ���������ǰ�ľ�ʫ���ܸ١�һ��
�ɺ衹��
LONG );
	set("exits", ([
		"out"   : __DIR__"neiting",
		"enter" : __DIR__"shihole2",
		"north" : __DIR__"shiroom01",
		"south" : __DIR__"shiroom02",
		"east"  : __DIR__"shiroom03",
		"west"  : __DIR__"shiroom04",
	]));
	set("objects", ([
		__DIR__"npc/wangwu": 1,
	]));
	setup();
}
