// /d/xiakedao/shihole6.c ���͵� ʯ��6

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
��ǰ�������������δ���κ�װ�Σ���ͺ�ֲڵ�ʯ��������С׭��
�������һ���ܸ٣������˹��桹����������һ��С��(xiaozi)����
��ʯ��ʯ������ذڷ��ţ������������£������ڲ�������
LONG );
	set("exits", ([
		"out"   : __DIR__"shihole5",
		"north" : __DIR__"shiroom21",
		"south" : __DIR__"shiroom22",
		"east"  : __DIR__"shiroom23",
		"west"  : __DIR__"shiroom24",
	]));
	set("item_desc", ([
		"��С�֡�": "С��д���ǣ���������ȳ���������Ωʯ�������񹦣�����...����������ּ���ģ���ѱ档\n"
	]));

	setup();
}
