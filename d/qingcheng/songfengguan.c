// Room: /qingcheng/songfengguan.c

inherit ROOM;
void create()
{
	set("short", "�ɷ��");
	set("long", @LONG
�������ɷ�ۣ������������������������У������˲ű�
��֮�ʡ�������������׺�����������ò������ΰ�С��ȴ����
��һ����ʦ�����г����ݻ����Լ�����ɲ������ơ�
LONG );
	set("exits", ([
		"north" : __DIR__"shangqing",
	]));
	set("objects", ([
		__DIR__"npc/hai" : 1,
	]));
	setup();
}

