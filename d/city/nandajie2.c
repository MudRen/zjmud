// Room: /city/nandajie2.c
inherit ROOM;

void create()
{
	set("short", "�ϴ��");
	set("long", @LONG
������һ�������Ľֵ��ϣ����ϱ���ͷ���졣����ͨ����
���ģ�������һ�ҹ˿��ڶ�Ĳ�ݣ����̾�����ʿ��������̸��˵�ء�����һ
�������¥������������Ц���Ǿ�����������������Ժ��
LONG );
	set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"lichunyuan",
		"south" : __DIR__"nanmen",
		"west"  : __DIR__"chaguan",
		"north" : __DIR__"nandajie1",
	]));
	set("objects", ([
		CLASS_D("shaolin") + "/tuoboseng" : 1,
 __DIR__"npc/liumang": 2,
	       "/clone/npc/walker" : 1,
	]));
	setup();
}
