inherit ROOM;

void create()
{
	set("short", "ɳ̲");
	set("long", @LONG
һƬ���ɫ��ɳ̲���ޱ��޼ʵĴ󺣾�����ǰ�ˡ������ĵĺ�ˮ����ӿ
���Ľ�׵��˻�������Ʈ������ı���ãã�Ĵ���û��һ�㷫Ӱ����Ŀ
Զ�������콻�紦����һƬ���ֲ��������Ǻ����������졣��������������
����ζ������΢΢���Ų��ˡ�
LONG );

	set("exits", ([
		"west" : __DIR__"haian",
	]));

	set("objects", ([
		"/d/tulong/yitian/npc/liuyun" : 1,
	]));

	set("outdoors", "tulong");
	setup();
}
